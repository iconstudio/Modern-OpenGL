#include "pch.hpp"
#include "Internal.hpp"
#undef CreateWindow
#undef CreateWindowEx

import Utility.Concurrency.Thread;
import Utility.Print;
import Glib;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Window;
import Glib.Window.ManagedWindow;

constexpr auto& my_windows_class = L"MY_CLASS";

int main(const int& argc, char** argv)
{
	util::Println("Program Initiated");
	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	gl::window::WindowProperty property = gl::window::CreatePropertyEx<L"TestWindow">();
	property.Register();

	util::Println("Creating a Window");
	auto window = gl::window::CreateWindowEx<L"TestWindow">(property, L"MY_TITLE", 50, 70, 400, 300);

	window.Awake();

	util::Println("Program Started");
	window.Start();

	util::Println("Program Ended");

	return 0;
}
