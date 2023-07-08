#include "pch.hpp"
import Utility.FixedString;
import Utility.Print;
import Glib;

static inline constexpr util::basic_fixed_string my_windows_class = L"MY_CLASS";

int main([[maybe_unused]] const int& argc, [[maybe_unused]] const char** const& argv)
{
	util::Println("== Program Initiated ==");
	auto framework = gl::CreateFramework();

	util::Println("== Creating the Client ==");
	framework->Initialize(gl::framework::Descriptor{});

	util::Println("== Program Started ==");
	framework->Run();

	util::Println("== Program Ended ==");

	return 0;
}
