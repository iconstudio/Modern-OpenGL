module;
#include <Windows.h>
#undef CreateWindow
#undef CreateWindowEx

module Glib.Framework;
import <exception>;
import <format>;
import Utility.Print;
import Glib.Display;
import Glib.Window.Factory;

static inline constexpr ::PIXELFORMATDESCRIPTOR opengl_format =
{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,                     // version number
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SUPPORT_COMPOSITION | PFD_SWAP_EXCHANGE,
	PFD_TYPE_RGBA,         // RGBA type
	32,
	0, 0, 0, 0, 0, 0,      // color bits ignored
	0,                     // no alpha buffer
	0,                     // shift bit ignored
	0,                     // no accumulation buffer
	0, 0, 0, 0,            // accum bits ignored
	32,                    // 32-bit z-buffer
	0,                     // no stencil buffer
	0,                     // no auxiliary buffer
	PFD_MAIN_PLANE,        // main layer
	0,                     // reserved
	0, 0, 0                // layer masks ignored
};

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
		//util::Println("예외 '{}'가 발생했습니다.", e.what());
		return framework::InitError::FailedOnCreatingWindow;
	}

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
		//util::Println("예외 '{}'가 발생했습니다.", e.what());
		return framework::InitError::FailedOnCreatingWindow;
	}

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

	myInstance->Start();
}

void ReadyDisplay() noexcept
{
	gl::display::dpi::SetDPIAware(true);

	if (gl::display::IsDimmingMode())
	{
		util::Println("Dark Mode");

		//constexpr int col_indices[] = { COLOR_WINDOW };
		//constexpr unsigned long colors[] = { RGB(255, 255, 255) };

		//::SetSysColors(1, col_indices, colors);
	}
	else
	{
		util::Println("Light Mode");
	}
}
