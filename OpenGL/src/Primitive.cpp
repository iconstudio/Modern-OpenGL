module;
#define NOMINMAX
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :Primitive;

gl::primitive::Context::Context(Primitive mode)
noexcept
{
	::glBegin(static_cast<GLenum>(mode));
}

gl::primitive::Context::~Context()
noexcept
{
	::glEnd();
}
void
gl::global::BeginPrimitives(gl::Primitive mode)
noexcept
{
	::glBegin(static_cast<GLenum>(mode));
}

void
gl::global::EndPrimitives()
noexcept
{
	::glEnd();
}
