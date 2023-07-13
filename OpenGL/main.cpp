import Utility.Print;
import Glib.Framework;

int main([[maybe_unused]] const int& argc, [[maybe_unused]] const char** const& argv)
{
	util::Println("== Program Initiated ==");
	auto framework = gl::CreateFramework();

	util::Println("== Creating the Client ==");
	framework->Initialize();

	util::Println("== Program Started ==");
	framework->Run();

	util::Println("== Program Ended ==");

	return 0;
}
