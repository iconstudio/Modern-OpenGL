module;
#include <Windows.h>

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

	return framework::InitError::Success;
}

void
gl::Framework::Run()
noexcept
{}
