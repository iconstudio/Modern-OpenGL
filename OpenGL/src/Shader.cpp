module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>

module Glib;
import <type_traits>;
import :Shader;

gl::Shader::Shader(shader::ShaderType sh_type)
noexcept
	: base()
	, myType(sh_type)
{
}

gl::Shader::~Shader()
noexcept
{}
