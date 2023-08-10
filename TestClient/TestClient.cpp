#pragma comment(lib, "Native.lib")
#pragma comment(lib, "OpenGL.lib")
#pragma comment(lib, "Utility.lib")

import <print>;
import <experimental/string>;
//import <mdspan>;

import <type_traits>;
import Glib;
import Glib.Framework;
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
	std::println("== Creating the Program ==");
	auto framework = gl::CreateFramework();

	std::println("== Program Initiated ==");
	gl::framework::Descriptor descriptor = gl::framework::MakeDefaultDescriptor();
	descriptor.glDescriptor.alphaBlend = true;
	descriptor.glDescriptor.doubleBuffered = true;
	descriptor.glDescriptor.keepAspectRatio = true;
	descriptor.glDescriptor.vSync = true;
	descriptor.isResizable = false;
	//descriptor.renderer = MyRenderer;

	std::println("== Initializing OpenGL ==");
	framework->Initialize(std::move(descriptor));

	std::println("== Program Started ==");
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
	vbo.Create(gl::buffer::BufferType::Array, gl::buffer::BufferUsage::StaticDraw, vertices, sizeof(vertices));

	framework->SetRenderer([&]() {
		vbo.Use();
	});

	framework->Run();

	std::println("== Program Ended ==");

	return 0;
}
