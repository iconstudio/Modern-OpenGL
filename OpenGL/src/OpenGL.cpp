module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>
#include <GL/GLu.h>

module Glib;
import <stdexcept>;
import <cstdio>;
import Utility.Print;
import Glib.Windows.Context;
import Glib.Windows.Client;
import Glib.Windows.ManagedClient;

constinit static const GLubyte* error_string = nullptr;

namespace gl
{
	void Initialize(win32::ManagedWindow& client)
	{
		win32::DeviceContext ctx = client.AcquireContext();

		//glMakeCurrentContext();

		GLenum err = ::glewInit();
		if (::glewIsSupported("GL_VERSION_4_6"))
		{
			std::printf("GL Version is 4.6\n");
		}

		if (GLEW_OK != err)
		{
			error_string = ::glewGetErrorString(err);
			const char* temp_msg = reinterpret_cast<const char*>(error_string);

			std::printf("GLEW Error: %s\n", temp_msg);
			//util::Println("Error: {}", temp_msg));
			//util::Println(std::format("Error: {}", temp_msg));
			//util::Println(std::vformat("Error: {}", std::make_format_args(temp_msg)));

			throw std::runtime_error("Failed to initialize GLEW");
		}
	}
}
