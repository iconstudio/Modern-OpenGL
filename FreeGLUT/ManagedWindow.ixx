module;
#include "Internal.hpp"

export module Glib.Window.ManagedWindow;
import <utility>;
import <memory>;
import <atomic>;
import <vector>;
import <unordered_map>;
import Utility.Constraints;
import Utility.Singleton;
import Utility.String;
import Utility.FixedString;
import Utility.Array;
import Utility.Atomic;
import Utility.Monad;
import Utility.Option;
import Utility.Concurrency.Thread;
import Utility.Concurrency.Thread.Unit;
import Glib.Rect;
import Glib.Window;
import Glib.Device.Coroutine;
import Glib.Device.Command;

export namespace gl::window
{
	template<util::basic_fixed_string Name>
	class [[nodiscard]] ManagedWindow
		: public ::std::enable_shared_from_this<ManagedWindow<Name>>
		, public util::Singleton<ManagedWindow<Name>>
	{
	public:
		static constexpr size_t WorkerCount = 4;

		using type = ManagedWindow<Name>;
		using base_shared_t = std::enable_shared_from_this<type>;
		using base_singleton_t = util::Singleton<type>;
		using under_shared_t = std::shared_ptr<type>;
		using under_weak_t = std::weak_ptr<type>;

		using unit_t = std::unique_ptr<util::ThreadUnit>;
		using pool_t = util::Array<unit_t, WorkerCount>;

		using event_id_t = device::DeviceCommandID;
		using event_handler_t = long long(*)(ManagedWindow&, unsigned long long, long long);

		static constexpr event_id_t DefaultEventID = device::DeviceCommandID::None;
		static constexpr device::DeviceCommand DefaultEvent = {};
		using event_t = device::DeviceCommand;
		using event_alert_t = std::atomic<event_t>;

		using event_storage_t = std::unordered_map<event_id_t, event_handler_t>;
		using event_iterator = event_storage_t::iterator;
		using event_const_iterator = event_storage_t::const_iterator;

		explicit ManagedWindow(Window&& window) noexcept
			: underlying(std::move(window)), myDimensions()
			, windowProcedureHandle(std::move(window.myProcecure))
			, myWorkers(), cancellationSource(), awaitFlag(DefaultEvent)
			, base_shared_t()
			, base_singleton_t(this)
		{
			myDimensions = underlying.GetDimensions();
			myEventHandlers.reserve(20);
		}

		void Awake() noexcept
		{
			size_t index = 0;
			for (unit_t& worker : myWorkers)
			{
				worker = std::make_unique<util::ThreadUnit>(ManagedWindow::Worker, cancellationSource.get_token(), util::ref(*this), util::ref(awaitFlag));

				++index;
			}

			underlying.Awake();
			underlying.Start();
		}

		/// <summary>
		/// The main loop
		/// </summary>
		void Start() noexcept
		{
			while (true)
			{
				underlying.UpdateOnce();
			}
		}

		//[[deprecated("Use Start() instead")]]
		inline void UpdateLoop(util::stop_token canceller) noexcept
		{
			while (underlying.UpdateOnce())
			{
				if (canceller.stop_requested())
					break;
			}
		}

		void AddEventHandler(event_id_t id, const event_handler_t& procedure) noexcept
		{
			myEventHandlers.insert(std::make_pair(id, procedure));
		}

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) noexcept = delete;
		ManagedWindow& operator=(const ManagedWindow&) = delete;
		ManagedWindow& operator=(ManagedWindow&&) noexcept = delete;

		static long long MainWorker(device::HWND, unsigned int, unsigned long long, long long) noexcept;
		static void Worker(ManagedWindow& self, event_alert_t& await_flag) noexcept
		{
			await_flag.wait(DefaultEvent, util::memory_order_relaxed);

			while (true)
			{
				auto event = await_flag.load();

				const event_iterator it = self.myEventHandlers.find(event.id);
				if (it != self.myEventHandlers.cend())
				{
					const event_handler_t& handler = it->second;

					handler(self, event.wParam, event.lParam);
				}

				await_flag.store(DefaultEvent, util::memory_order_acquire);
				await_flag.wait(DefaultEvent, util::memory_order_release);
			}
		}

	private:
		bool AlertEvent(const event_id_t& event_id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			if (myEventHandlers.contains(event_id))
			{
				awaitFlag.store(event_t(event_id, lhs, rhs, 0));
				awaitFlag.notify_one();
				return true;
			}
			else
			{
				return false;
			}
		}

		[[nodiscard]]
		util::Monad<event_handler_t> FindEventHandler(const event_id_t& event_id)
			noexcept
		{
			const event_iterator it = myEventHandlers.find(event_id);
			if (it == myEventHandlers.cend())
			{
				return util::nullopt;
			}
			else
			{
				return it->second;
			}
		}

		Window underlying;
		Rect myDimensions;
		WindowProcedure windowProcedureHandle = nullptr;

		// flat map
		event_storage_t myEventHandlers{};

		pool_t myWorkers;
		util::CancellationSource cancellationSource;
		util::atomic<int> awaitCount = 0;
		event_alert_t awaitFlag;

		util::Option<bool> optionFullscreen{ false };
		util::atomic_bool isRenderingNow = false;
	};

	template<util::basic_fixed_string Name>
	long long
		ManagedWindow<Name>::MainWorker(device::HWND hwnd // underlying.myHandle
	, unsigned int id
	, unsigned long long wparam, long long lparam)
		noexcept
	{
		const event_id_t msg = static_cast<event_id_t>(id);
		ManagedWindow<Name>* self = ManagedWindow<Name>::Instance;

		switch (msg)
		{
			// Started by close button or system menu or Alt+F4
			case event_id_t::Close:
			{
				DestroyWindow(hwnd);
			}
			break;

			// Started by DestroyWindow
			case event_id_t::Destroy:
			{
				PostQuitMessage(0);
			}
			break;

			// Started by WM_DESTROY
			case event_id_t::Quit:
			{
				//KillTimer(hwnd, RENDER_TIMER_ID);
			}
			break;

			// Clean memory up
			// Started by WM_DESTROY
			case event_id_t::CleanupMemory:
			{
				// Forced stop code
				return 0;
			}

			case event_id_t::KeyDown:
			//[[fallthrough]]
			case event_id_t::KeyUp:
			{
				return 0;
			}
			break;

			default:
			{
				if (self)
				{
					self->AlertEvent(msg, wparam, lparam);
				}
			}
			break;
		}

		return DefWindowProc(hwnd, id, wparam, lparam);
	}
}
