module;
module Glib.Window.ManagedWindow;
import <exception>;
import Glib.Device.Utility;

gl::window::ManagedWindow::ManagedWindow(gl::window::Window&& window, int number_of_workers)
	: underlying(std::move(window))
	, workerCount(number_of_workers), terminateLatch(number_of_workers)
	, base_shared_t()
{
	myDimensions = underlying.GetDimensions();
	myEventHandlers.reserve(20);
	myWorkers.reserve(number_of_workers);

	underlying.SetInternalUserData(reinterpret_cast<long long>(this));
}

gl::window::managed_window::AwakeResult
gl::window::ManagedWindow::Awake()
noexcept
{
	try
	{
		for (size_t index = 0; index < workerCount; ++index)
		{
			myWorkers.emplace_back(std::make_unique<util::jthread>(Worker, cancellationSource.get_token(), std::ref(*this), std::ref(awaitFlag)));
		}
	}
	catch (...)
	{
		return managed_window::AwakeResult::FailedOnCreatingWorkers;
	}

	try
	{
		myCoroutines = std::make_unique<coro_storage>();
	}
	catch (...)
	{
		return managed_window::AwakeResult::FailedOnCreatingCoroutines;
	}

	underlying.Awake();
	underlying.Start();
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

void
gl::window::ManagedWindow::AddEventHandler(gl::window::ManagedWindow::event_id_t id, const gl::window::ManagedWindow::event_handler_t& procedure)
noexcept
{
	myEventHandlers.insert(std::make_pair(id, procedure));
}

void
gl::window::ManagedWindow::SetCaptureMouse(const bool& flag)
noexcept
{
	isCapturing = flag;
}

void
gl::window::ManagedWindow::StartCoroutine(gl::window::ManagedWindow::coro_t&& coroutine)
noexcept
{
	ResumeTopCoroutine();

	//myCoroutines->push(std::move(coroutine));
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

bool
gl::window::ManagedWindow::AlertEvent(const event_id_t& event_id, const unsigned long long& lhs, const long long& rhs)
noexcept
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
gl::window::ManagedWindow::DefaultSysKeyEvent(gl::window::ManagedWindow& self, device::io::KeyCode code, bool is_first)
noexcept
{
	if (is_first && code == device::io::KeyCode::F4)
	{
		self.underlying.SendCommand(event_id_t::Close);
	}
}

long long
gl::window::ManagedWindow::MainWorker(gl::device::HWND hwnd, unsigned int id, unsigned long long wparam, long long lparam)
noexcept
{
	const event_id_t msg = static_cast<event_id_t>(id);

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

void
gl::window::ManagedWindow::Worker(util::CancellationToken stop_token, gl::window::ManagedWindow& self, event_alert_t& await_flag)
noexcept
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
