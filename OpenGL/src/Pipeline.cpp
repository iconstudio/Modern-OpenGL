module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>

module Glib;
import <type_traits>;
import :Pipeline;

gl::Pipeline::Pipeline()
noexcept
	: base()
	, myShaders()
{
	base::SetID(::glCreateProgram());

	myShaders.reserve(DefaultPreShaders);
}

gl::Pipeline::~Pipeline()
noexcept
{
	if (IsValid())
	{
		::glDeleteProgram(myID);
	}
}
