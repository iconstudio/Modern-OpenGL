export module Glib.Window.ManagedWindow;
import <utility>;
import <memory>;
import <vector>;
import <stack>;
import <unordered_map>;
import Utility.Constraints;
import Utility.Array;
import Utility.Atomic;
import Utility.Monad;
import Utility.Concurrency.Thread;
import Glib.Rect;
import Glib.Definitions;
import Glib.Device.IO;
export import Glib.Device.Event;
export import Glib.Window.Coroutine;
import Glib.Window;

namespace gl::window
{
	export inline namespace managed_window
	{
		enum class [[nodiscard]] AwakeResult
		{
			Success = 0,
			FailedOnCreatingWorkers = 1,
			FailedOnCreatingCoroutines = 2,
			FailedOnPrepareEvent = 3,
		};

		//using KeyDownEventHandler = std::move_only_function<void(ManagedWindow&, device::io::KeyCode, bool is_first)>;
		using KeyDownEventHandler = void(*)(ManagedWindow&, device::io::KeyCode, bool is_first) noexcept;
		using KeyUpEventHandler = void(*)(ManagedWindow&, device::io::KeyCode) noexcept;
		using SysKeyDownEventHandler = void(*)(ManagedWindow&, device::io::KeyCode, bool is_first) noexcept;
		using SysKeyUpEventHandler = void(*)(ManagedWindow&, device::io::KeyCode) noexcept;
		using CharDownEventHandler = void(*)(ManagedWindow&, char32_t, long long) noexcept;
		using CharUpEventHandler = void(*)(ManagedWindow&, char32_t, long long) noexcept;
		using RenderEventHandler = void(*)(ManagedWindow&, device::GraphicDeviceContext&) noexcept;
	}

	export class [[nodiscard]] ManagedWindow
		: public std::enable_shared_from_this<ManagedWindow>
	{
	protected:
		using type = ManagedWindow;

		using base_shared_t = std::enable_shared_from_this<type>;
		using under_shared_t = std::shared_ptr<type>;
		using under_weak_t = std::weak_ptr<type>;

		using unit_t = std::unique_ptr<util::jthread>;
		using pool_t = std::vector<unit_t>;
		using coro_t = gl::window::Coroutine;
		using coro_storage = std::stack<coro_t>;

	public:
		using event_id_t = device::EventID;
		using event_handler_t = void(*)(ManagedWindow&, unsigned long long, long long) noexcept;

		using event_t = device::Event;
		using event_alert_t = std::atomic<event_t>;

		using event_storage_t = std::unordered_map<event_id_t, event_handler_t>;
		using event_iterator = event_storage_t::iterator;
		using event_const_iterator = event_storage_t::const_iterator;

		explicit ManagedWindow(Window&& window, int number_of_workers);

		managed_window::AwakeResult Awake() noexcept;
		void Start() noexcept;
		[[noreturn]]
		void Destroy() noexcept;

		[[nodiscard]] device::DeviceContext AcquireContext() const noexcept;
		[[nodiscard]] device::GraphicDeviceContext AcquireRenderContext() const noexcept;

		void SetPowerSave(const bool& flag) noexcept;
		void SetCaptureMouse(const bool& flag = true) noexcept;

		void AddEventHandler(event_id_t id, const event_handler_t& procedure) noexcept;
		KeyDownEventHandler SetKeyDownHandler(KeyDownEventHandler handler) noexcept;
		KeyUpEventHandler SetKeyUpHandler(KeyUpEventHandler handler) noexcept;
		SysKeyDownEventHandler SetSysKeyDownHandler(SysKeyDownEventHandler handler) noexcept;
		SysKeyUpEventHandler SetSysKeyUpHandler(SysKeyUpEventHandler handler) noexcept;
		CharDownEventHandler SetCharDownHandler(CharDownEventHandler handler) noexcept;
		CharUpEventHandler SetCharUpHandler(CharUpEventHandler handler) noexcept;
		void StartCoroutine(coro_t&& coroutine) noexcept;

		[[nodiscard]] std::exception_ptr GetException() const noexcept;

		static long long MainWorker(device::HWND, unsigned int, unsigned long long, long long) noexcept;
		static void Worker(util::CancellationToken stop_token, ManagedWindow& self, event_alert_t& await_flag) noexcept;

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) = delete;
		ManagedWindow& operator=(const ManagedWindow&) = delete;
		ManagedWindow& operator=(ManagedWindow&&) = delete;

	private:
		bool AlertEvent(const event_id_t& event_id, const unsigned long long& lhs, const long long& rhs) noexcept;
		[[nodiscard]]
		util::Monad<event_handler_t> FindEventHandler(const event_id_t& event_id) noexcept;

		bool TryCaptureMouse() noexcept;
		void ResetMouseCapture() noexcept;
		void ClearMouseCapturing() noexcept;
		[[nodiscard]]
		bool IsMouseCaptured() const noexcept;
		void ResumeTopCoroutine() noexcept;

		static void KeyboardHandler(ManagedWindow&, unsigned long long, long long) noexcept;
		static void CharKeyHandler(ManagedWindow&, unsigned long long, long long) noexcept;
		static void DefaultSysKeyEvent(ManagedWindow& self, device::io::KeyCode code, bool is_first) noexcept;

		Window underlying;
		Rect myDimensions{};

		// flat map
		event_storage_t myEventHandlers{};
		static inline constexpr device::Event DefaultEvent = {};

		managed_window::KeyDownEventHandler onKeyDown = nullptr;
		managed_window::KeyUpEventHandler onKeyUp = nullptr;
		managed_window::SysKeyDownEventHandler onSysDown = DefaultSysKeyEvent;
		managed_window::SysKeyUpEventHandler onSysUp = nullptr;
		managed_window::CharDownEventHandler onChrDown = nullptr;
		managed_window::CharUpEventHandler onChrUp = nullptr;
		managed_window::RenderEventHandler onRender = nullptr;

		pool_t myWorkers{};
		size_t workerCount = 0;

		util::atomic<int> awaitCount = 0;
		event_alert_t awaitFlag{ DefaultEvent };

		util::atomic_bool isRunning = false;
		util::CancellationSource cancellationSource{};
		util::atomic_int terminateLatch;

		util::atomic_bool isFocused = false;
		util::atomic_bool isMouseHover = false;
		util::atomic_bool isCapturing = false;
		util::atomic_bool isRenderingNow = false;
		util::atomic_bool noPowerSaves = false;

		std::unique_ptr<coro_storage> myCoroutines{};

		std::exception_ptr lastException{};
	};
}
