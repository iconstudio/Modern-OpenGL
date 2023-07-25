import <type_traits>;
import Utility.Print;
import Glib;
import Glib.Framework;

void DefaultRenderer() noexcept
{
	gl::primitive::Context ctx{ gl::Primitive::Triangles };

	gl::primitive::SetColour(1.0f, 0.0f, 0.0f);
	gl::primitive::Vertex(0, -1, 0);

	gl::primitive::SetColour(0.0f, 1.0f, 0.0f);
	gl::primitive::Vertex(1, 0, 0);

	gl::primitive::SetColour(0.0f, 0.0f, 1.0f);
	gl::primitive::Vertex(0, 1, 0);
}

int main([[maybe_unused]] const int& argc, [[maybe_unused]] const char** const& argv)
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
	framework->SetRenderer(DefaultRenderer);

	framework->Initialize(std::move(descriptor));

	util::Println("== Program Started ==");
	framework->Run();

	util::Println("== Program Ended ==");

	return 0;
}
