export module Glib.Window.ManagedWindow;
import <utility>;
import <memory>;
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
	class [[nodiscard]] ManagedWindow
		: public ::std::enable_shared_from_this<ManagedWindow>
	{
	public:
		static constexpr size_t WorkerCount = 4;

		using unit_t = std::unique_ptr<util::ThreadUnit>;
		using pool_t = util::Array<unit_t, WorkerCount>;

		using event_id_t = typename device::DeviceCommandID;

		using event_handler_t = void(*)(ManagedWindow&, unsigned long long, long long);
		static constexpr event_id_t DefaultEventID = device::DeviceCommandID::None;
		using event_t = std::pair<event_id_t, event_handler_t>;
		using event_storage_t = std::unordered_map<event_id_t, event_handler_t>;
		using event_iterator = event_storage_t::iterator;
		using event_const_iterator = event_storage_t::const_iterator;

		using event_alert_t = std::atomic<event_id_t>;

		explicit ManagedWindow(Window&& window) noexcept
			: underlying(std::move(window)), myDimensions()
			, windowProcedureHandle(std::move(window.myProcecure))
			, optionFullscreen(false), isRenderingNow(false)
			, myEventHandlers()
			, myWorkers(), cancellationSource(), awaitFlag(DefaultEventID)
			, std::enable_shared_from_this<ManagedWindow>()
		{
			myDimensions = underlying.GetDimensions();
			myEventHandlers.reserve(20);
		}

		void Awake()
		{
			size_t index = 0;
			for (unit_t& worker : myWorkers)
			{
				worker = std::make_unique<util::ThreadUnit>(Worker, cancellationSource.get_token(), util::ref(*this), util::ref(awaitFlag));

				++index;
			}

			underlying.Awake();
		}

		void Start() noexcept
		{
			underlying.Start();
		}

		void AddEventHandler(event_id_t id, const event_handler_t& procedure) noexcept
		{
			myEventHandlers.insert(std::make_pair(id, procedure));
		}

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) noexcept = default;
		ManagedWindow& operator=(const ManagedWindow&) = delete;
		ManagedWindow& operator=(ManagedWindow&&) noexcept = default;

	private:
		static void Worker(ManagedWindow& self, event_alert_t& await_flag) noexcept;
		static void EventHandler(ManagedWindow& self, const event_id_t& msg, unsigned long long wparam, long long lparam) noexcept;

		void AlertEvent(const event_id_t& event_id) noexcept
		{
			awaitFlag.store(event_id);
			awaitFlag.notify_one();
		}

		util::Monad<event_handler_t> FindEventHandler(const event_id_t& event_id) noexcept
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

		util::Option<bool> optionFullscreen;

		WindowProcedure windowProcedureHandle = nullptr;
		bool isRenderingNow = false;

		// flat map
		event_storage_t myEventHandlers;

		util::CancellationSource cancellationSource;
		pool_t myWorkers;
		util::atomic<int> awaitCount = 0;
		event_alert_t awaitFlag;
	};

	void ManagedWindow::Worker(ManagedWindow& self, event_alert_t& await_flag) noexcept
	{
		await_flag.wait(DefaultEventID, util::memory_order_relaxed);

		while (true)
		{
			EventHandler(self, await_flag.load(), 0, 0);

			const event_iterator it = self.myEventHandlers.find(await_flag.load());
			if (it != self.myEventHandlers.cend())
			{
				const event_handler_t& handler = it->second;

				handler(self, 0, 0);
			}

			await_flag.store(DefaultEventID, util::memory_order_acquire);
			await_flag.wait(DefaultEventID, util::memory_order_release);
		}
	}

	void ManagedWindow::EventHandler(ManagedWindow& self, const event_id_t& id, unsigned long long wparam, long long lparam) noexcept
	{
		const util::Monad<event_handler_t> handle_pair = self.FindEventHandler(id);
		if (handle_pair)
		{
			const event_handler_t& handler = *handle_pair;
			if (handler)
			{
				handler(self, wparam, lparam);
			}
		}
	}
}
