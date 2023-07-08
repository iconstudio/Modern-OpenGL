module;
#include <Windows.h>
#undef CreateWindow
#undef CreateWindowEx

module Glib.Framework;
import Utility.Print;
import Glib.Display;
import Glib.Window.Factory;

void ReadyDisplay() noexcept;

gl::framework::InitError
gl::Framework::Initialize(const gl::framework::Descriptor& setup)
{
	ReadyDisplay();

	myInstance = window::CreateWindowEx<L"ManagedWindow">(setup.title, setup.wx, setup.wy, setup.ww, setup.wh);

	return framework::InitError::Success;
}

gl::framework::InitError
gl::Framework::Initialize(gl::framework::Descriptor&& setup)
{
	ReadyDisplay();

	myInstance = window::CreateWindowEx<L"ManagedWindow">(std::move(setup.title), std::move(setup.wx), std::move(setup.wy), std::move(setup.ww), std::move(setup.wh));

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
{}

void ReadyDisplay() noexcept
{
	gl::display::dpi::SetDPIAware(true);

	if (gl::display::IsDimmingMode())
	{
		util::Println("Dark Mode");
	}
	else
	{
		util::Println("Light Mode");
	}
}
