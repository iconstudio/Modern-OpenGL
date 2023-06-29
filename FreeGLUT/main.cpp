#include "pch.hpp"
import Utility.FixedString;
import Utility.Print;
import Glib;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Window;
import Glib.Window.ManagedWindow;

static inline constexpr util::basic_fixed_string my_windows_class = L"MY_CLASS";

int main([[maybe_unused]] const int& argc, [[maybe_unused]] const char** const& argv)
{
	util::Println("== Program Initiated ==");

	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	gl::window::WindowProperty property = gl::window::CreatePropertyEx<my_windows_class>();
	property.Register();

	util::Println("== Creating the Client ==");
	auto window = gl::window::CreateWindowEx<my_windows_class>(property, L"MY_TITLE", 50, 70, 400, 300);

	window.Awake();

	util::Println("== Program Started ==");
	gl::Start();
	window.Start();

	util::Println("== Program Ended ==");

	return 0;
}
