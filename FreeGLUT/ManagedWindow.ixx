export module Glib.Window.ManagedWindow;
import <cstdio>;
import <iostream>;
import <utility>;
import <memory>;
import <vector>;
import <stack>;
import <unordered_map>;
import Utility.Constraints;
import Utility.Reflection.Unique;
import Utility.FixedString;
import Utility.Array;
import Utility.Atomic;
import Utility.Monad;
import Utility.Option;
import Utility.Concurrency.Thread;
import Glib.Rect;
import Glib.Device.Event;
import Glib.Device.Brush;
export import Glib.Device.IO;
import Glib.Device.Utility;
export import Glib.Window.Coroutine;
import Glib.Window;

export namespace gl::window
{
	class [[nodiscard]] ManagedWindow
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
		using event_handler_t = void(*)(ManagedWindow&, unsigned long long, long long);

		using event_t = device::Event;
		using event_alert_t = std::atomic<event_t>;

		using event_storage_t = std::unordered_map<event_id_t, event_handler_t>;
		using event_iterator = event_storage_t::iterator;
		using event_const_iterator = event_storage_t::const_iterator;

		using KeyDownEventHandler = void(*)(ManagedWindow&, device::io::KeyCode, bool is_first);
		using KeyUpEventHandler = void(*)(ManagedWindow&, device::io::KeyCode);
		using SysKeyDownEventHandler = void(*)(ManagedWindow&, device::io::KeyCode, bool is_first);
		using SysKeyUpEventHandler = void(*)(ManagedWindow&, device::io::KeyCode);
		using CharDownEventHandler = void(*)(ManagedWindow&, char32_t, long long);
		using CharUpEventHandler = void(*)(ManagedWindow&, char32_t, long long);

		explicit ManagedWindow(Window&& window, int number_of_workers);
		void Awake() noexcept
		{
			for (size_t index = 0; index < workerCount; ++index)
			{
				myWorkers.emplace_back(std::make_unique<util::jthread>(Worker, cancellationSource.get_token(), std::ref(*this), std::ref(awaitFlag)));
			}

			myCoroutines = std::make_unique<coro_storage>();

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

		void SetCaptureMouse(const bool& flag = true) noexcept
		{
			isCapturing = flag;
		}

		void StartCoroutine(coro_t&& coroutine) noexcept
		{
			//ResumeTopCoroutine();

			//myCoroutines->push(std::move(coroutine));
		}

		[[noreturn]]
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

		static void Worker(util::CancellationToken stop_token, ManagedWindow& self, event_alert_t& await_flag) noexcept;

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) = delete;
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

		/// <summary>
		/// Only on the main thread
		/// </summary>
		bool TryCaptureMouse() noexcept
		{
			if (isCapturing)
			{
				device::io::CaptureMouse(underlying.GetHandle());
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// Only on the main thread
		/// </summary>
		void ResetMouseCapture() noexcept
		{
			device::io::ResetMouseCapture(underlying.GetHandle());
		}

		/// <summary>
		/// Only on the main thread
		/// </summary>
		void ClearMouseCapturing() noexcept
		{
			ResetMouseCapture();
			isCapturing = false;
		}

		/// <summary>
		/// Only on the main thread
		/// </summary>
		[[nodiscard]]
		bool IsMouseCaptured() const noexcept
		{
			return device::io::IsMouseCaptured(underlying.GetHandle());
		}

		void ResumeTopCoroutine() noexcept
		{
			if (!myCoroutines->empty())
			{
				myCoroutines->top().Resume();
			}
		}

		static void DefaultSysKeyEvent(ManagedWindow& self, device::io::KeyCode code, bool is_first) noexcept
		{
			if (is_first && code == device::io::KeyCode::F4)
			{
				self.underlying.SendCommand(event_id_t::Close);
			}
		}

		Window underlying;
		Rect myDimensions{};

		// flat map
		event_storage_t myEventHandlers{};
		static inline constexpr device::Event DefaultEvent = {};

		KeyDownEventHandler keyDownHandler = nullptr;
		KeyUpEventHandler keyUpHandler = nullptr;
		SysKeyDownEventHandler sysDownHandler = DefaultSysKeyEvent;
		SysKeyUpEventHandler sysUpHandler = nullptr;
		CharDownEventHandler chrDownHandler = nullptr;
		CharUpEventHandler chrUpHandler = nullptr;

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

		std::unique_ptr<coro_storage> myCoroutines{};
	};

	long long
		ManagedWindow::MainWorker(gl::device::HWND hwnd, unsigned int id, unsigned long long wparam, long long lparam) noexcept
	{
		const gl::window::ManagedWindow::event_id_t msg = static_cast<event_id_t>(id);

		device::IWindowHandle ctx{ std::move(hwnd) };

		ManagedWindow* const& self = reinterpret_cast<ManagedWindow*>(ctx.GetInternalUserData());

		switch (msg)
		{
			case gl::device::kb::Pressed:
			{
				std::printf("[Key Pressed] %lld\n", wparam);
				if (auto& key_dw_handler = self->keyDownHandler; key_dw_handler)
				{
					key_dw_handler(*self, static_cast<device::io::KeyCode>(wparam), device::io::IsFirstPress(lparam));
				}
			}
			break;

			case gl::device::kb::Released:
			{
				std::printf("[Key Released] %lld\n", wparam);
				if (auto& key_up_handler = self->keyUpHandler; key_up_handler)
				{
					key_up_handler(*self, static_cast<device::io::KeyCode>(wparam));
				}
			}
			break;

			case gl::device::kb::AltPressed:
			{
				std::printf("[System Key Pressed] %lld\n", wparam);
				if (auto& sys_dw_handler = self->sysDownHandler; sys_dw_handler)
				{
					sys_dw_handler(*self, static_cast<device::io::KeyCode>(wparam), device::io::IsFirstPress(lparam));
				}
			}
			break;

			case gl::device::kb::AltReleased:
			{
				std::printf("[System Key Released] %lld\n", wparam);
				if (auto& sys_up_handler = self->sysUpHandler; sys_up_handler)
				{
					sys_up_handler(*self, static_cast<device::io::KeyCode>(wparam));
				}
			}
			break;

			case gl::device::kb::CharPressed:
			case gl::device::kb::AltCharPressed:
			{
				std::printf("[Chr Pressed] %lld\n", wparam);
				if (auto& chr_dw_handler = self->chrDownHandler; chr_dw_handler)
				{
					chr_dw_handler(*self, static_cast<char32_t>(wparam), lparam);
				}
			}
			break;

			case gl::device::kb::CharReleased:
			case gl::device::kb::AltCharReleased:
			{
				std::printf("[Chr Released] %lld\n", wparam);
				if (auto& chr_up_handler = self->chrUpHandler; chr_up_handler)
				{
					chr_up_handler(*self, static_cast<char32_t>(wparam), lparam);
				}
			}
			break;

			case event_id_t::ChangedDPI:
			{
				std::printf("[ChangedDPI]\n");
				ctx.Redraw(true);
			}
			break;

			case event_id_t::ChangedTheme:
			{
				std::printf("[ChangedTheme]\n");
				ctx.Redraw(true);
			}
			break;

			case event_id_t::ChangedStaticColor:
			{
				std::printf("[ChangedStaticColor]\n");
				ctx.Redraw(true);
			}
			break;

			case event_id_t::ChangedUserColor:
			{
				std::printf("[ChangedUserColor] Colour is changed to %lld. Is Fluent: %lld\n", wparam, lparam);
				ctx.Redraw(true);
			}
			break;

			case event_id_t::Activate:
			{
				const unsigned short trigger = device::LOWORD(wparam);

				if (trigger == device::DeviceActivation::Inactivated)
				{
					std::printf("[Activate] Unfocused\n");
					self->isFocused = false;
					self->isMouseHover = false;
					self->ResetMouseCapture();
				}
				else
				{
					std::printf("[Activate] Focused\n");
					self->isFocused = true;
				}
			}
			break;

			case gl::device::mb::Covered:
			{
				if (self->isFocused)
				{
					std::printf("[Mouse Hovered]\n");
					self->isMouseHover = true;
					self->TryCaptureMouse();
				}
			}
			break;

			case gl::device::mb::Uncovered:
			{
				std::printf("[Mouse Left]\n");
				self->isMouseHover = false;
			}
			break;

			case event_id_t::SetKeyboardFocus:
			{
				std::printf("[SetKeyboardFocus]\n");
			}
			break;

			case event_id_t::KillKeyboardFocus:
			{
				std::printf("[KillKeyboardFocus]\n");
			}
			break;

			case event_id_t::Initiate:
			{
				std::printf("[Preprocess]\n");
			}
			return ctx.DefaultWndProc(id, wparam, lparam);

			case event_id_t::Create:
			{
				std::printf("[Create]\n");
			}
			return ctx.DefaultWndProc(id, wparam, lparam);

			// Started by close button or system menu [or Alt+F4]
			case event_id_t::Close:
			{
				ctx.Destroy();
				self->isFocused = false;
				self->ClearMouseCapturing();
			}
			break;

			// Started by DestroyWindow
			case event_id_t::Destroy:
			{
				device::PostQuitMessage(0);

				if (self)
				{
					self->Destroy();
				}
			}
			break;

			// Started by WM_DESTROY
			case event_id_t::Quit:
			{
				//KillTimer(ctx.GetHandle(), RENDER_TIMER_ID);
			}
			break;

			//[[fallthrough]]
			default:
			{
				if (self)
				{
					if (self->AlertEvent(msg, wparam, lparam))
					{
						break;
					}
					else
					{
						self->ResumeTopCoroutine();
						// will be resumed by yielder
					}
				}

				return ctx.DefaultWndProc(id, wparam, lparam);
			}
			break;
		}

		return 0;
	}

	void gl::window::ManagedWindow::Worker(util::CancellationToken stop_token, ManagedWindow& self, event_alert_t& await_flag) noexcept
	{
		await_flag.wait(DefaultEvent, util::memory_order_relaxed);

		while (true)
		{
			if (stop_token.stop_requested())
			{
				return;
			}

			auto event = await_flag.load();
			self.FindEventHandler(event.id).if_then([&](const event_handler_t& handler) noexcept {
				handler(self, event.wParam, event.lParam);
			});

			await_flag.store(DefaultEvent, util::memory_order_acquire);
			await_flag.wait(DefaultEvent, util::memory_order_release);
		}

		auto& latch = self.terminateLatch;

		const int count = latch.load(util::memory_order_acquire);
		if (0 == util::atomic_fetch_sub(&latch, 1))
		{
			latch.notify_all();

			return;
		}
		else
		{
			latch.wait(count, util::memory_order_release);
		}
	}
}
