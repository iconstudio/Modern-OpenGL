module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#undef CreateWindow
#undef CreateWindowEx

module Glib.Framework;
import <cstdio>;
import <exception>;
import <format>;
import Glib.Display;
import Glib.Device.Context;
import Glib.Window.Factory;

void ReadyDisplay() noexcept;

gl::framework::InitError
gl::Framework::Initialize(const gl::framework::Descriptor& setup)
{
	ReadyDisplay();

	try
	{
		myInstance = window::CreateWindowEx<L"ManagedWindow">(setup.title, setup.wx, setup.wy, setup.ww, setup.wh);
	}
	catch (const std::exception& e)
	{
		std::printf("Exception: '%s'", e.what());
		return framework::InitError::FailedOnCreatingWindow;
	}

	if (unsigned long error = glContext.Initialize(myInstance->AcquireContext()); 0 != error)
	{
		std::printf("Pixel Formatting Error: %lu\n", error);
		return framework::InitError::FailedOnSettingPixelFormat;
	}

	myInstance->SetPowerSave(setup.isPowersave);

	return framework::InitError::Success;
}

gl::framework::InitError
gl::Framework::Initialize(gl::framework::Descriptor&& setup)
{
	ReadyDisplay();

	try
	{
		myInstance = window::CreateWindowEx<L"ManagedWindow">(std::move(setup.title), std::move(setup.wx), std::move(setup.wy), std::move(setup.ww), std::move(setup.wh));
	}
	catch (const std::exception& e)
	{
		std::printf("Exception: '%s'", e.what());
		return framework::InitError::FailedOnCreatingWindow;
	}

	if (unsigned long error = glContext.Initialize(myInstance->AcquireContext()); 0 != error)
	{
		std::printf("Pixel Formatting Error: %lu\n", error);
		return framework::InitError::FailedOnSettingPixelFormat;
	}

	myInstance->SetPowerSave(std::move(setup.isPowersave));

	return framework::InitError::Success;
}

gl::framework::InitError
gl::Framework::Initialize()
{
	return Initialize(framework::MakeDefaultDescriptor());
}

void
gl::Framework::Run()
noexcept
{
	using enum window::managed_window::AwakeResult;
	const auto awakenening = myInstance->Awake();

	if (awakenening != Success)
	{
		//util::Println("Failed on awakening. (code: {}).", static_cast<int>(awakenening));

		std::rethrow_exception(myInstance->GetException());
		return;
	}

	SetRenderer(DefaultRenderer);

	myInstance->Start();
}

void
gl::Framework::AddEventHandler(gl::EventID id, const event_handler_t& procedure)
noexcept
{
	myInstance->AddEventHandler(id, procedure);
}

void
gl::Framework::AddEventHandler(gl::EventID id, event_handler_t&& procedure)
noexcept
{
	myInstance->AddEventHandler(id, std::move(procedure));
}

void
gl::Framework::RemoveEventHandler(gl::EventID id)
noexcept
{
	myInstance->RemoveEventHandler(id);
}

void
gl::Framework::SetRenderer(render_t handler)
noexcept
{
	myInstance->SetRenderer(
		[this, localRenderer = std::move(handler)](
		ManagedWindow& window,
		GraphicDeviceContext& ctx) {
		glContext.Begin(ctx);
		localRenderer(window);
		glContext.End();
	});
}

void
gl::Framework::DefaultRenderer(gl::Framework::handle_t& window)
noexcept
{
	// Do Nothing
}

void ReadyDisplay() noexcept
{
	gl::display::dpi::SetDPIAware(true);

	//constexpr int col_indices[] = { COLOR_WINDOW };
	//constexpr unsigned long colors[] = { RGB(255, 255, 255) };
	//::SetSysColors(1, col_indices, colors);

	if (gl::display::IsDimmingMode())
	{
		std::puts("Dark Mode");
	}
	else
	{
		std::puts("Light Mode");
	}
}

std::shared_ptr<gl::Framework>
gl::CreateFramework()
noexcept
{
	return std::make_shared<Framework>();
}
