module;
#include "Internal.hpp"

export module Glib.Window.ManagedWindow;
import <utility>;
import <memory>;
import <atomic>;
import <vector>;
import <latch>;
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
export import Glib.Device.IO.Keyboard.KeyCodes;
export import Glib.Device.IO.Keyboard.Flags;

#undef CreateWindow
#undef CreateWindowEx

export namespace gl::window
{
	using KeyEventHandler = void(*)(device::io::KeyCode, long long);
	using CharEventHandler = void(*)(char32_t, long long);

	template<util::basic_fixed_string ID, size_t WorkerCount = 4>
	class [[nodiscard]] ManagedWindow
		: public ::std::enable_shared_from_this<ManagedWindow<ID>>
		, public util::Singleton<ManagedWindow<ID>>
	{
	public:
		using type = ManagedWindow<ID>;
		using name_type = decltype(ID);

		using base_shared_t = std::enable_shared_from_this<type>;
		using base_singleton_t = util::Singleton<type>;
		using under_shared_t = std::shared_ptr<type>;
		using under_weak_t = std::weak_ptr<type>;

		using unit_t = std::unique_ptr<util::jthread>;
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
				worker = std::make_unique<util::jthread>(ManagedWindow::Worker, cancellationSource.get_token(), util::ref(*this), util::ref(awaitFlag));

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
			isRunning = true;

			while (true)
			{
				if (cancellationSource.stop_requested())
				{
					break;
				}

				underlying.UpdateOnce();
			}
		}

		void AddEventHandler(event_id_t id, const event_handler_t& procedure) noexcept
		{
			myEventHandlers.insert(std::make_pair(id, procedure));
		}

		void Destroy() noexcept
		{
			if (isRunning)
			{
				cancellationSource.request_stop();
				awaitFlag.notify_all();

				for (unit_t& worker : myWorkers)
				{
					worker->detach();
				}

				isRunning = false;
			}
		}

		static long long MainWorker(device::HWND, unsigned int, unsigned long long, long long) noexcept;

		static void Worker(util::CancellationToken stop_token, ManagedWindow& self, event_alert_t& await_flag) noexcept
		{
			await_flag.wait(DefaultEvent, util::memory_order_relaxed);

			while (true)
			{
				if (stop_token.stop_requested())
				{
					return;
				}

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

			self.terminateLatch.arrive_and_wait();
		}

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) noexcept = delete;
		ManagedWindow& operator=(const ManagedWindow&) = delete;
		ManagedWindow& operator=(ManagedWindow&&) noexcept = delete;

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
		util::atomic_bool isRunning = false;
		util::CancellationSource cancellationSource;
		std::latch terminateLatch{ WorkerCount };

		util::atomic<int> awaitCount = 0;
		event_alert_t awaitFlag;

		util::Option<bool> optionFullscreen{ false };
		util::atomic_bool isRenderingNow = false;
	};

	template<util::basic_fixed_string ID, size_t WorkerCount>
	long long
		ManagedWindow<ID, WorkerCount>::MainWorker(device::HWND hwnd // underlying.myHandle
	, unsigned int id
	, unsigned long long wparam, long long lparam)
		noexcept
	{
		const event_id_t msg = static_cast<event_id_t>(id);

		ManagedWindow<ID>* self = ManagedWindow<ID>::Instance;
		auto& key_handler = self->eventOfKeyHandler;
		auto& char_handler = self->eventOfCharHandler;

		switch (msg)
		{
			case event_id_t::KeyDown:
			case event_id_t::KeyUp:
			case event_id_t::SysKeyDown:
			case event_id_t::SysKeyUp:
			{
				if (key_handler)
			{
					key_handler(static_cast<device::io::KeyCode>(wparam), lparam);
				}
			}
				return 0;

			case event_id_t::Char:
			case event_id_t::DeadChar:
			case event_id_t::SysChar:
			case event_id_t::SysDeadChar:
			{
				if (char_handler)
			{
					char_handler(static_cast<char32_t>(wparam), lparam);
				}
			}
				return 0;

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

				if (self)
				{
					self->Destroy();
				}
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

			//[[fallthrough]]
			default:
			{
				if (self)
				{
					self->AlertEvent(msg, wparam, lparam);
				}
				return DefWindowProc(hwnd, id, wparam, lparam);
			}
			break;
		}

		return 0;
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(properties, title, style, option, x, y, width, height) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(std::move(properties), title, style, option, x, y, width, height) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const Rect& dimension
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(properties, title, style, option, dimension) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const Rect& dimension
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(std::move(properties), title, style, option, dimension) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(properties, title, style, x, y, width, height) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(std::move(properties), title, style, x, y, width, height) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(properties, title, style, dimension) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(std::move(properties), title, style, options::Default, dimension) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(const WindowProperty& properties
		, const std::wstring_view& title
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(properties, title, x, y, width, height) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(WindowProperty&& properties
		, const std::wstring_view& title
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(std::move(properties), title, x, y, width, height) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(const WindowProperty& properties
		, const std::wstring_view& title
		, const Rect& dimension
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(properties, title, dimension) };
	}

	template<util::basic_fixed_string NID, size_t Workers = 4>
	[[nodiscard]]
	ManagedWindow<NID, Workers> CreateWindowEx(WindowProperty&& properties
		, const std::wstring_view& title
		, const Rect& dimension
	) noexcept
	{
		return ManagedWindow<NID>{ CreateWindow(std::move(properties), title, dimension) };
	}

	template<util::basic_fixed_string NID>
	[[nodiscard]]
	WindowProperty CreatePropertyEx() noexcept
	{
		constexpr std::wstring_view class_name_view{ NID };

		return gl::window::CreateProperty(device::GetProcessInstance(), ManagedWindow<NID>::MainWorker, class_name_view.data());
	}

	template<util::basic_fixed_string NID, typename IconType, typename CursorType>
	[[nodiscard]]
	WindowProperty CreatePropertyEx(IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, const ::HBRUSH& background
		, const wchar_t* const& menu_name
	) noexcept
	{
		constexpr std::wstring_view class_name_view{ NID };

		return gl::window::CreateProperty(device::GetProcessInstance(), ManagedWindow<NID>::MainWorker
			, class_name_view.data()
			, std::forward<IconType>(icon), std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, background
			, menu_name);
	}
}
