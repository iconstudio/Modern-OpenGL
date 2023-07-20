module;
module Glib.Windows.ManagedClient;
import <cstdio>;
import <exception>;
import Glib.Windows.Utility;
import Glib.Windows.Context;
import Glib.Windows.Context.Renderer;
import Glib.Windows.CompatibleContext;

gl::win32::ManagedWindow::ManagedWindow(gl::win32::Window&& window, int number_of_workers)
	: underlying(std::move(window))
	, workerCount(number_of_workers), terminateLatch(number_of_workers)
	, base_shared_t()
{
	myDimensions = underlying.GetDimensions();
	myEventHandlers.reserve(255);

	myWorkers.reserve(number_of_workers);
}

gl::win32::managed_window::AwakeResult
gl::win32::ManagedWindow::Awake()
noexcept
{
	try
	{
		underlying.SetInternalUserData(reinterpret_cast<long long>(this));

		for (size_t index = 0; index < workerCount; ++index)
		{
			myWorkers.emplace_back(std::make_unique<util::jthread>(Worker, cancellationSource.get_token(), std::ref(*this), std::ref(awaitFlag)));
		}
	}
	catch (...)
	{
		lastException = std::current_exception();

		return managed_window::AwakeResult::FailedOnCreatingWorkers;
	}

	try
	{
		myCoroutines = std::make_unique<coro_storage>();
	}
	catch (...)
	{
		lastException = std::current_exception();

		return managed_window::AwakeResult::FailedOnCreatingCoroutines;
	}

	underlying.Awake();

	try
	{
		AddEventHandler(gl::win32::kb::Pressed, KeyboardHandler);
		AddEventHandler(gl::win32::kb::Released, KeyboardHandler);
		AddEventHandler(gl::win32::kb::AltPressed, KeyboardHandler);
		AddEventHandler(gl::win32::kb::AltReleased, KeyboardHandler);

		AddEventHandler(gl::win32::kb::CharPressed, CharKeyHandler);
		AddEventHandler(gl::win32::kb::CharReleased, CharKeyHandler);
		AddEventHandler(gl::win32::kb::AltCharPressed, CharKeyHandler);
		AddEventHandler(gl::win32::kb::AltCharReleased, CharKeyHandler);
	}
	catch (...)
	{
		lastException = std::current_exception();

		return managed_window::AwakeResult::FailedOnPrepareEvent;
	}

	return managed_window::AwakeResult::Success;
}

void
gl::win32::ManagedWindow::Start()
noexcept
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

	isRunning = false;
}

long long
gl::win32::ManagedWindow::MainWorker(gl::win32::HWND hwnd, unsigned int id, unsigned long long wparam, long long lparam)
noexcept
{
	const event_id_t msg = static_cast<event_id_t>(id);

	IWindow control{ std::move(hwnd) };

	ManagedWindow* const& self = reinterpret_cast<ManagedWindow*>(control.GetInternalUserData());

	switch (msg)
	{
		case event_id_t::Paint:
		{
			if (nullptr == self)
			{
				std::printf("[Initiated] First Rendering\n");
				break;
			}

			self->isRenderingNow.store(true, util::memory_order_relaxed);
			GraphicDeviceContext render_ctx = control.AcquireRenderContext();

			if (auto& renderer = self->onRender; renderer)
			{
				renderer(*self, render_ctx);
			}

			self->isRenderingNow.store(false, util::memory_order_relaxed);
		}
		break;

		case event_id_t::ChangedDPI:
		{
			std::printf("[ChangedDPI]\n");
			self->ClearWindow();
		}
		break;

		case event_id_t::ChangedTheme:
		{
			std::printf("[ChangedTheme]\n");
			self->ClearWindow();
		}
		break;

		case event_id_t::ChangedStaticColor:
		{
			std::printf("[ChangedStaticColor]\n");
			self->ClearWindow();
		}
		break;

		case event_id_t::ChangedUserColor:
		{
			std::printf("[ChangedUserColor] Colour is changed to %lld. Is Fluent: %lld\n", wparam, lparam);
			self->ClearWindow();
		}
		break;

		case event_id_t::Activate:
		{
			if (nullptr == self)
			{
				std::printf("[Initiated]\n");
				break;
			}

			const unsigned short trigger = LOWORD(wparam);

			if (trigger == DeviceActivation::Inactivated)
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

		case gl::win32::mb::Covered:
		{
			if (self->isFocused)
			{
				std::printf("[Mouse Hovered]\n");
				self->isMouseHover = true;
				self->TryCaptureMouse();
			}
		}
		break;

		case gl::win32::mb::Uncovered:
		{
			std::printf("[Mouse Left]\n");
			self->isMouseHover = false;
		}
		break;

		case event_id_t::KeyboardFocus:
		{
			std::printf("[KeyboardFocus]\n");
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
		return control.DefaultWndProc(id, wparam, lparam);

		case event_id_t::Create:
		{
			std::printf("[Create]\n");
		}
		return control.DefaultWndProc(id, wparam, lparam);

		// Started by close button or system menu [or Alt+F4]
		case event_id_t::Close:
		{
			std::printf("[Close]\n");
			control.Destroy();
			self->isFocused = false;
			self->ClearMouseCapturing();
		}
		break;

		case event_id_t::Resize:
		{
			//std::printf("[Resize]\n");
			//self->ClearWindow();
			self->AlertEvent(msg, wparam, lparam);
		}
		break;

		// Started by DestroyWindow
		case event_id_t::Destroy:
		{
			std::printf("[Destroy]\n");
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
			//KillTimer(control.GetHandle(), RENDER_TIMER_ID);
		}
		break;

		case event_id_t::SysCommand:
		{
			SystemCommand cmd = static_cast<SystemCommand>(wparam);
			switch (cmd)
			{
				case SystemCommand::MonitorPower:
				if (self->noPowerSaves.load(util::memory_order_relaxed))
				{
					break;
				}
			}

			return control.DefaultWndProc(id, wparam, lparam);
		}

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

			return control.DefaultWndProc(id, wparam, lparam);
		}
	}

	return 0;
}

void
gl::win32::ManagedWindow::Worker(util::CancellationToken stop_token, gl::win32::ManagedWindow& self, event_alert_t& await_flag)
noexcept
{
	await_flag.wait(DefaultEvent, util::memory_order_relaxed);

	while (true)
	{
		if (stop_token.stop_requested())
		{
			break;
		}

		auto event = await_flag.load(util::memory_order_acquire);
		self.FindEventHandler(event.id).if_then(
			[&](const event_handler_t& handler) noexcept {
			handler(self, event.wParam, event.lParam);
		});

		await_flag.store(DefaultEvent, util::memory_order_release);
		await_flag.wait(DefaultEvent, util::memory_order_acquire);
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

void
gl::win32::ManagedWindow::AddEventHandler(gl::win32::ManagedWindow::event_id_t id, const gl::win32::ManagedWindow::event_handler_t& procedure)
noexcept
{
	myEventHandlers.insert(std::make_pair(id, procedure));
}

void
gl::win32::ManagedWindow::AddEventHandler(event_id_t id, event_handler_t&& procedure)
noexcept
{
	myEventHandlers.insert(std::make_pair(id, std::move(procedure)));
}

void
gl::win32::ManagedWindow::RemoveEventHandler(gl::win32::ManagedWindow::event_id_t id)
noexcept
{
	myEventHandlers.erase(id);
}

gl::win32::managed_window::KeyDownEventHandler
gl::win32::ManagedWindow::SetKeyDownHandler(managed_window::KeyDownEventHandler handler)
noexcept
{
	return std::exchange(onKeyDown, std::move(handler));
}

gl::win32::managed_window::KeyUpEventHandler
gl::win32::ManagedWindow::SetKeyUpHandler(managed_window::KeyUpEventHandler handler)
noexcept
{
	return std::exchange(onKeyUp, std::move(handler));
}

gl::win32::managed_window::SysKeyDownEventHandler
gl::win32::ManagedWindow::SetSysKeyDownHandler(managed_window::SysKeyDownEventHandler handler)
noexcept
{
	return std::exchange(onSysDown, std::move(handler));
}

gl::win32::managed_window::SysKeyUpEventHandler
gl::win32::ManagedWindow::SetSysKeyUpHandler(managed_window::SysKeyUpEventHandler handler)
noexcept
{
	return std::exchange(onSysUp, std::move(handler));
}

gl::win32::managed_window::CharDownEventHandler
gl::win32::ManagedWindow::SetCharDownHandler(managed_window::CharDownEventHandler handler)
noexcept
{
	return std::exchange(onChrDown, std::move(handler));
}

gl::win32::managed_window::CharUpEventHandler
gl::win32::ManagedWindow::SetCharUpHandler(managed_window::CharUpEventHandler handler)
noexcept
{
	return std::exchange(onChrUp, std::move(handler));
}

void
gl::win32::ManagedWindow::SetRenderer(const managed_window::RenderEventHandler& handler)
noexcept
{
	onRender = handler;
}

void
gl::win32::ManagedWindow::SetRenderer(managed_window::RenderEventHandler&& handler) noexcept
{
	onRender = std::move(handler);
}

bool
gl::win32::ManagedWindow::AlertEvent(const event_id_t& event_id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	if (myEventHandlers.contains(event_id))
	{
		awaitFlag.store(event_t(event_id, lhs, rhs, 0), util::memory_order_release);
		awaitFlag.notify_one();

		return true;
	}
	else
	{
		return false;
	}
}

util::Monad<gl::win32::ManagedWindow::event_handler_t>
gl::win32::ManagedWindow::FindEventHandler(const event_id_t& event_id)
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

void
gl::win32::ManagedWindow::StartCoroutine(gl::win32::ManagedWindow::coro_t&& coroutine)
noexcept
{
	ResumeTopCoroutine();

	//myCoroutines->push(std::move(coroutine));
}

std::exception_ptr
gl::win32::ManagedWindow::GetException()
const noexcept
{
	return lastException;
}

void
gl::win32::ManagedWindow::Destroy()
noexcept
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

gl::win32::DeviceContext
gl::win32::ManagedWindow::AcquireContext()
const noexcept
{
	return underlying.AcquireContext();
}

gl::win32::GraphicDeviceContext
gl::win32::ManagedWindow::AcquireRenderContext()
const noexcept
{
	return underlying.AcquireRenderContext();
}

void
gl::win32::ManagedWindow::SetPowerSave(const bool& flag)
noexcept
{
	noPowerSaves = !flag;
}

void
gl::win32::ManagedWindow::SetCaptureMouse(const bool& flag)
noexcept
{
	isCapturing = flag;
}

bool
gl::win32::ManagedWindow::TryCaptureMouse()
noexcept
{
	if (isCapturing)
	{
		io::CaptureMouse(underlying.GetHandle());
		return true;
	}
	else
	{
		return false;
	}
}

void
gl::win32::ManagedWindow::ResetMouseCapture()
noexcept
{
	io::ResetMouseCapture(underlying.GetHandle());
}

void
gl::win32::ManagedWindow::ClearMouseCapturing()
noexcept
{
	ResetMouseCapture();
	isCapturing = false;
}

bool
gl::win32::ManagedWindow::IsMouseCaptured() const
noexcept
{
	return io::IsMouseCaptured(underlying.GetHandle());
}

void
gl::win32::ManagedWindow::ResumeTopCoroutine()
noexcept
{
	if (!myCoroutines->empty())
	{
		myCoroutines->top().Resume();
	}
}

bool
gl::win32::ManagedWindow::ClearWindow(const gl::Rect& rect)
noexcept
{
	return underlying.Clear(rect);
}

bool
gl::win32::ManagedWindow::ClearWindow()
noexcept
{
	return underlying.Clear();
}

void
gl::win32::ManagedWindow::KeyboardHandler(gl::win32::ManagedWindow& self, unsigned long long wparam, long long lparam)
noexcept
{
	self.ClearWindow();

	const bool is_press = io::IsPressing(lparam);
	const bool is_first = io::IsFirstPress(lparam);
	const bool is_sys = io::IsWithAltKey(lparam);

	if (!is_press)
	{
		if (is_sys)
		{
			std::printf("[System Key Released] %lld\n", wparam);
			if (nullptr != self.onSysUp)
			{
				self.onSysUp(self, static_cast<io::KeyCode>(wparam));
			}
		}
		else
		{
			std::printf("[Key Released] %lld\n", wparam);
			if (nullptr != self.onKeyUp)
			{
				self.onKeyUp(self, static_cast<io::KeyCode>(wparam));
			}
		}
	}
	else if (is_first)
	{
		if (is_sys)
		{
			std::printf("[System Key Pressed] %lld\n", wparam);
			if (nullptr != self.onSysDown)
			{
				self.onSysDown(self, static_cast<io::KeyCode>(wparam), is_first);
			}
		}
		else
		{
			std::printf("[Key Pressed] %lld\n", wparam);
			if (nullptr != self.onKeyDown)
			{
				self.onKeyDown(self, static_cast<io::KeyCode>(wparam), is_first);
			}
		}
	}
}

void
gl::win32::ManagedWindow::CharKeyHandler(gl::win32::ManagedWindow& self, unsigned long long wparam, long long lparam)
noexcept
{
	const bool is_press = io::IsPressing(lparam);
	const bool is_first = io::IsFirstPress(lparam);
	const bool is_sys = io::IsWithAltKey(lparam);

	if (!is_press)
	{
		if (is_sys)
		{
			std::printf("[System Chr Released] %lld\n", wparam);
		}
		else
		{
			std::printf("[Chr Released] %lld\n", wparam);
		}

		if (nullptr != self.onChrUp)
		{
			self.onChrUp(self, static_cast<char32_t>(wparam), lparam);
		}
	}
	else if (is_first)
	{
		if (is_sys)
		{
			std::printf("[System Chr Pressed] %lld\n", wparam);
		}
		else
		{
			std::printf("[Chr Pressed] %lld\n", wparam);
		}

		if (nullptr != self.onChrDown)
		{
			self.onChrDown(self, static_cast<char32_t>(wparam), is_first);
		}
	}
}

void
gl::win32::ManagedWindow::DefaultSysKeyEvent(gl::win32::ManagedWindow& self, io::KeyCode code, bool is_first)
noexcept
{
	if (is_first && code == io::KeyCode::F4)
	{
		self.underlying.SendCommand(event_id_t::Close, 0, 0);
	}
}
