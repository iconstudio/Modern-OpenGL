import <cstdio>;
import <type_traits>;
import Glib;
import Glib.Client;
import Glib.Legacy.Primitive;
import Glib.Texture;

void MyRenderer() noexcept
{
	using namespace gl::legacy;
	primitive::Context ctx{ gl::Primitive::Triangles };

	primitive::SetColour(1.0f, 0.0f, 0.0f);
	primitive::Vertex(0, -1, 0);

	primitive::SetColour(0.0f, 1.0f, 0.0f);
	primitive::Vertex(1, 0, 0);

	primitive::SetColour(0.0f, 0.0f, 1.0f);
	primitive::Vertex(0, 1, 0);
}

int main([[maybe_unused]] const int& argc, [[maybe_unused]] const char** const& argv)
{
	std::puts("== Creating the Program ==");
	auto framework = client::CreateFramework();

	std::puts("== Program Initiated ==");
	client::framework::Descriptor descriptor = client::framework::MakeDefaultDescriptor();
	descriptor.glDescriptor.alphaBlend = true;
	descriptor.glDescriptor.doubleBuffered = true;
	descriptor.glDescriptor.keepAspectRatio = true;
	descriptor.glDescriptor.vSync = true;
	descriptor.isResizable = false;
	descriptor.renderer = MyRenderer;

	std::puts("== Initializing OpenGL ==");
	framework->Initialize(std::move(descriptor));

	std::puts("== Program Started ==");
	gl::Texture texture = gl::LoadTexture(L"testimg.jpg");

	gl::BufferLayout layout{};
	layout.AddElement<float>(3);

	constexpr float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f, // bottom right
		0.0f, 0.5f, 0.0f, // top
	};

	gl::BufferObject vbo{};
	vbo.SetData(vertices, sizeof(vertices), gl::buffer::BufferUsage::StaticDraw);

	framework->Run();

	std::puts("== Program Ended ==");

	return 0;
}
