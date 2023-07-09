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
	}
	else
	{
		util::Println("Light Mode");
	}
}
