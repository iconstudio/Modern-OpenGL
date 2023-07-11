module;
module Glib.Window.ManagedWindow;
import <cstdio>;
import <exception>;
import Glib.Device.Utility;
import Glib.Device.Context;
import Glib.Device.Context.Renderer;
import Glib.Device.CompatibleContext;

gl::window::ManagedWindow::ManagedWindow(gl::window::Window&& window, int number_of_workers)
	: underlying(std::move(window))
	, workerCount(number_of_workers), terminateLatch(number_of_workers)
	, base_shared_t()
{
	myDimensions = underlying.GetDimensions();
	myEventHandlers.reserve(20);
	myWorkers.reserve(number_of_workers);
}

gl::window::managed_window::AwakeResult
gl::window::ManagedWindow::Awake()
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
		AddEventHandler(gl::device::kb::Pressed, KeyboardHandler);
		AddEventHandler(gl::device::kb::Released, KeyboardHandler);
		AddEventHandler(gl::device::kb::AltPressed, KeyboardHandler);
		AddEventHandler(gl::device::kb::AltReleased, KeyboardHandler);

		AddEventHandler(gl::device::kb::CharPressed, CharKeyHandler);
		AddEventHandler(gl::device::kb::CharReleased, CharKeyHandler);
		AddEventHandler(gl::device::kb::AltCharPressed, CharKeyHandler);
		AddEventHandler(gl::device::kb::AltCharReleased, CharKeyHandler);
	}
	catch (...)
	{
		lastException = std::current_exception();

		return managed_window::AwakeResult::FailedOnPrepareEvent;
	}

	return managed_window::AwakeResult::Success;
}

void
gl::window::ManagedWindow::Start()
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
}

bool
gl::window::ManagedWindow::AlertEvent(const event_id_t& event_id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	if (myEventHandlers.contains(event_id))
	{
		awaitFlag.store(event_t(event_id, lhs, rhs, 0), util::memory_order_release);
		awaitFlag.notify_one();

		//::InvalidateRect(control, nullptr, TRUE);
		return true;
	}
	else
	{
		return false;
	}
}

long long
gl::window::ManagedWindow::MainWorker(gl::device::HWND hwnd, unsigned int id, unsigned long long wparam, long long lparam)
noexcept
{
	const event_id_t msg = static_cast<event_id_t>(id);

	device::IWindow control{ std::move(hwnd) };

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

			device::GraphicDeviceContext render_ctx = control.AcquireRenderContext();

			if (auto& renderer = self->onRender; renderer)
			{
				renderer(*self, render_ctx);
			}
		}
		break;

		case event_id_t::ChangedDPI:
		{
			std::printf("[ChangedDPI]\n");
			control.Redraw(true);
		}
		break;

		case event_id_t::ChangedTheme:
		{
			std::printf("[ChangedTheme]\n");
			control.Redraw(true);
		}
		break;

		case event_id_t::ChangedStaticColor:
		{
			std::printf("[ChangedStaticColor]\n");
			control.Redraw(true);
		}
		break;

		case event_id_t::ChangedUserColor:
		{
			std::printf("[ChangedUserColor] Colour is changed to %lld. Is Fluent: %lld\n", wparam, lparam);
			control.Redraw(true);
		}
		break;

		case event_id_t::Activate:
		{
			if (nullptr == self)
			{
				std::printf("[Initiated]\n");
				break;
			}

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

		// Started by DestroyWindow
		case event_id_t::Destroy:
		{
			std::printf("[Destroy]\n");
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
			//KillTimer(control.GetHandle(), RENDER_TIMER_ID);
		}
		break;

		case event_id_t::SysCommand:
		{
			device::SystemCommand cmd = static_cast<device::SystemCommand>(wparam);
			switch (cmd)
			{
				case device::SystemCommand::MonitorPower:
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
gl::window::ManagedWindow::Worker(util::CancellationToken stop_token, gl::window::ManagedWindow& self, event_alert_t& await_flag)
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
gl::window::ManagedWindow::AddEventHandler(gl::window::ManagedWindow::event_id_t id, const gl::window::ManagedWindow::event_handler_t& procedure)
noexcept
{
	myEventHandlers.insert(std::make_pair(id, procedure));
}

gl::window::managed_window::KeyDownEventHandler&&
gl::window::ManagedWindow::SetKeyDownHandler(managed_window::KeyDownEventHandler handler)
noexcept
{
	auto old = std::move(onKeyDown);
	onKeyDown = std::move(handler);

	return std::move(old);
}

gl::window::managed_window::KeyUpEventHandler&&
gl::window::ManagedWindow::SetKeyUpHandler(managed_window::KeyUpEventHandler handler)
noexcept
{
	auto old = std::move(onKeyUp);
	onKeyUp = std::move(handler);

	return std::move(old);
}

gl::window::managed_window::SysKeyDownEventHandler&&
gl::window::ManagedWindow::SetSysKeyDownHandler(managed_window::SysKeyDownEventHandler handler)
noexcept
{
	auto old = std::move(onSysDown);
	onSysDown = std::move(handler);

	return std::move(old);
}

gl::window::managed_window::SysKeyUpEventHandler&&
gl::window::ManagedWindow::SetSysKeyUpHandler(managed_window::SysKeyUpEventHandler handler)
noexcept
{
	auto old = std::move(onSysUp);
	onSysUp = std::move(handler);

	return std::move(old);
}

gl::window::managed_window::CharDownEventHandler&&
gl::window::ManagedWindow::SetCharDownHandler(managed_window::CharDownEventHandler handler)
noexcept
{
	auto old = std::move(onChrDown);
	onChrDown = std::move(handler);

	return std::move(old);
}

gl::window::managed_window::CharUpEventHandler&&
gl::window::ManagedWindow::SetCharUpHandler(managed_window::CharUpEventHandler handler)
noexcept
{
	auto old = std::move(onChrUp);
	onChrUp = std::move(handler);

	return std::move(old);
}

util::Monad<gl::window::ManagedWindow::event_handler_t>
gl::window::ManagedWindow::FindEventHandler(const event_id_t& event_id)
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
gl::window::ManagedWindow::StartCoroutine(gl::window::ManagedWindow::coro_t&& coroutine)
noexcept
{
	ResumeTopCoroutine();

	//myCoroutines->push(std::move(coroutine));
}

std::exception_ptr
gl::window::ManagedWindow::GetException()
const noexcept
{
	return lastException;
}

void
gl::window::ManagedWindow::Destroy()
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

gl::device::DeviceContext
gl::window::ManagedWindow::AcquireContext()
const noexcept
{
	return underlying.AcquireContext();
}

gl::device::GraphicDeviceContext
gl::window::ManagedWindow::AcquireRenderContext()
const noexcept
{
	return underlying.AcquireRenderContext();
}

void
gl::window::ManagedWindow::SetPowerSave(const bool& flag)
noexcept
{
	noPowerSaves = !flag;
}

void
gl::window::ManagedWindow::SetCaptureMouse(const bool& flag)
noexcept
{
	isCapturing = flag;
}

bool
gl::window::ManagedWindow::TryCaptureMouse()
noexcept
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

void
gl::window::ManagedWindow::ResetMouseCapture()
noexcept
{
	device::io::ResetMouseCapture(underlying.GetHandle());
}

void
gl::window::ManagedWindow::ClearMouseCapturing()
noexcept
{
	ResetMouseCapture();
	isCapturing = false;
}

bool
gl::window::ManagedWindow::IsMouseCaptured() const
noexcept
{
	return device::io::IsMouseCaptured(underlying.GetHandle());
}

void
gl::window::ManagedWindow::ResumeTopCoroutine()
noexcept
{
	if (!myCoroutines->empty())
	{
		myCoroutines->top().Resume();
	}
}

void
gl::window::ManagedWindow::KeyboardHandler(gl::window::ManagedWindow& self, unsigned long long wparam, long long lparam)
noexcept
{
	const bool is_press = device::io::IsPressing(lparam);
	const bool is_first = device::io::IsFirstPress(lparam);
	const bool is_sys = device::io::IsWithAltKey(lparam);

	if (!is_press)
	{
		if (is_sys)
		{
			std::printf("[System Key Released] %lld\n", wparam);
			if (nullptr != self.onSysUp)
			{
				self.onSysUp(self, static_cast<device::io::KeyCode>(wparam));
			}
		}
		else
		{
			std::printf("[Key Released] %lld\n", wparam);
			if (nullptr != self.onKeyUp)
			{
				self.onKeyUp(self, static_cast<device::io::KeyCode>(wparam));
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
				self.onSysDown(self, static_cast<device::io::KeyCode>(wparam), is_first);
			}
		}
		else
		{
			std::printf("[Key Pressed] %lld\n", wparam);
			if (nullptr != self.onKeyDown)
			{
				self.onKeyDown(self, static_cast<device::io::KeyCode>(wparam), is_first);
			}
		}
	}
}

void
gl::window::ManagedWindow::CharKeyHandler(gl::window::ManagedWindow& self, unsigned long long wparam, long long lparam)
noexcept
{
	const bool is_press = device::io::IsPressing(lparam);
	const bool is_first = device::io::IsFirstPress(lparam);
	const bool is_sys = device::io::IsWithAltKey(lparam);

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
gl::window::ManagedWindow::DefaultSysKeyEvent(gl::window::ManagedWindow& self, device::io::KeyCode code, bool is_first)
noexcept
{
	if (is_first && code == device::io::KeyCode::F4)
	{
		self.underlying.SendCommand(event_id_t::Close, 0, 0);
	}
}
