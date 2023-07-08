module;
#include <Windows.h>
#undef CreateWindow
#undef CreateWindowEx

module Glib.Framework;
import Utility.Print;
import Glib.Display;
import Glib.Window.Factory;

gl::framework::InitError
gl::Framework::Initialize(const gl::framework::Descriptor& setup)
{
	display::dpi::SetDPIAware(true);

	if (display::IsDimmingMode())
	{
		util::Println("Dark Mode");
	}
	else
	{
		util::Println("Light Mode");
	}

	myInstance = window::CreateWindowEx<L"ManagedWindow">(setup.title, setup.wx, setup.wy, setup.ww, setup.wh);

	return framework::InitError::Success;
}

gl::framework::InitError
gl::Framework::Initialize()
{
	return Initialize(framework::DefaultDescriptor());
}

void
gl::Framework::Run()
noexcept
{}
