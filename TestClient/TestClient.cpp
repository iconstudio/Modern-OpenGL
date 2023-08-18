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

#define GLSL(code) #code

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
	gl::BufferLayout test_layout{};
	test_layout.AddElement<float>(3);

	constexpr float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f, // bottom right
		0.0f, 0.5f, 0.0f, // top
	};

	gl::BufferObject vbo{};

	vbo.SetLayout(test_layout);
	vbo.Create(gl::buffer::BufferType::Array, gl::buffer::BufferUsage::StaticDraw, vertices, sizeof(vertices));

	gl::shader::ShaderType shty0 = gl::shader::ShaderType::None;
	gl::shader::ShaderType shty1 = gl::shader::ShaderType::Vertex;
	gl::shader::ShaderType shty2 = gl::shader::ShaderType::Fragment;
	gl::shader::ShaderType shty3 = gl::shader::ShaderType::Pixel;
	gl::shader::ShaderType shty4 = gl::shader::ShaderType::Tessellation;
	gl::shader::ShaderType shty5 = gl::shader::ShaderType::TessellEvaluation;
	gl::shader::ShaderType shty6 = gl::shader::ShaderType::Geometry;

	std::println("{} {} {} {} {} {} {}", shty0, shty1, shty2, shty3, shty4, shty5, shty6);

	gl::Shader vshader{ shty1 };
	auto result = vshader.Compile(GLSL
	(
		in vec3 aPos;

		void main()
		{
			gl_Position = vec4(aPos, 1.0);
		}
	));

	gl::Shader fshader{ shty2 };
	result = fshader.Compile
	(
		"out vec4 FragColor;"

		"void main()"
		"{"
		"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
		"}"
	);
	//gl::Texture texture = gl::LoadTexture(L"testimg.jpg");

	gl::Pipeline pipeline{};
	pipeline.AddShader(std::move(vshader));
	pipeline.AddShader(std::move(fshader));

	const auto sherr = vshader.GetLastError();
	std::println("{}", sherr);

	framework->SetRenderer([&]() {
		pipeline.Use();
		vbo.Use();
		pipeline.Render(gl::Primitive::TriangleFan, 3);
	});

	framework->Run();

	std::println("== Program Ended ==");

	return 0;
}
