import Utility.Print;
import Glib.Framework;

int main()
{
	util::Println("== Creating the Program ==");
	auto framework = gl::CreateFramework();

	util::Println("== Program Initiated ==");
	gl::framework::Descriptor descriptor = gl::framework::MakeDefaultDescriptor();
	descriptor.glDescriptor.alphaBlend = true;
	descriptor.glDescriptor.doubleBuffered = true;
	descriptor.glDescriptor.keepAspectRatio = true;
	descriptor.glDescriptor.vSync = true;
	descriptor.isResizable = false;

	framework->Initialize(std::move(descriptor));

	util::Println("== Program Started ==");
	framework->Run();

	util::Println("== Program Ended ==");

	return 0;
}
