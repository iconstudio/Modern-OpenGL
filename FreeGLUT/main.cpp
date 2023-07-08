#include "pch.hpp"
import Utility.FixedString;
import Utility.Print;
import Glib;
import Glib.Window.Coroutine;
import Glib.Window.Factory;

static inline constexpr util::basic_fixed_string my_windows_class = L"MY_CLASS";

gl::window::Coroutine test_coroutine() noexcept
{
	co_yield gl::window::WaitForSeconds(4000);
}

int main([[maybe_unused]] const int& argc, [[maybe_unused]] const char** const& argv)
{
	util::Println("== Program Initiated ==");

	util::Println("== Creating the Client ==");
	auto window = gl::window::CreateWindowEx<my_windows_class>(L"MY_TITLE", 50, 70, 640, 480);

	window->Awake();

	util::Println("== Program Started ==");

	gl::Start();

	//window.StartCoroutine(test_coroutine());
	window->Start();

	util::Println("== Program Ended ==");

	return 0;
}
