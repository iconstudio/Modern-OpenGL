module;
#include <Windows.h>
#include "glew.h"
#include <gl/GL.h>
#include <gl/GLu.h>

module Glib;
import <stdexcept>;

constinit static const GLubyte* version_string = nullptr;
constinit static const GLubyte* version_vendor = nullptr;
constinit static const GLubyte* version_render = nullptr;
constinit static const GLubyte* version_shader = nullptr;
constinit static const GLubyte* version_extent = nullptr;

std::string_view
gl::info::GetVersion()
noexcept
{
	version_string = glGetString(GL_VERSION);
	return reinterpret_cast<const char*>(version_string);
}

std::string_view
gl::info::GetVendor()
noexcept
{
	version_vendor = glGetString(GL_VENDOR);
	return reinterpret_cast<const char*>(version_vendor);
}

std::string_view
gl::info::GetRenderer()
noexcept
{
	version_render = glGetString(GL_RENDERER);
	return reinterpret_cast<const char*>(version_render);
}

std::string_view
gl::info::GetExtensions()
noexcept
{
	version_extent = glGetString(GL_EXTENSIONS);
	return reinterpret_cast<const char*>(version_extent);
}

std::string_view
gl::info::GetShadingLanguageVersion()
noexcept
{
	version_shader = glGetString(GL_SHADING_LANGUAGE_VERSION);
	return reinterpret_cast<const char*>(version_shader);
}
