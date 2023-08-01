module;
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
module Glib;
import <stdexcept>;
import <cstdio>;
import Utility.Print;

constinit static const GLubyte* error_string = nullptr;

namespace gl
{
	void Initialize()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			error_string = glewGetErrorString(err);
			const char* temp_msg = reinterpret_cast<const char*>(error_string);

			std::printf("Error: %s\n", temp_msg);
			//util::Println("Error: {}", temp_msg));
			//util::Println(std::format("Error: {}", temp_msg));
			//util::Println(std::vformat("Error: {}", std::make_format_args(temp_msg)));

			throw std::runtime_error("Failed to initialize GLEW");
		}
	}
}
