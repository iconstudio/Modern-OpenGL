module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :TransformState;

void
gl::transform::SetMode(gl::TransformMode mode)
noexcept
{
	::glMatrixMode(static_cast<GLenum>(mode));
}

void
gl::transform::PushState()
noexcept
{
	::glPushMatrix();
	::glLoadIdentity();
}

void
gl::transform::PopState()
noexcept
{
	::glPopMatrix();
}

gl::transform::Context::Context()
noexcept
{
	::glPushMatrix();
}

gl::transform::Context::Context(gl::TransformMode mode)
noexcept
{
	::glPushMatrix();
	::glMatrixMode(static_cast<GLenum>(mode));
	::glLoadIdentity();
}

gl::transform::Context::~Context()
noexcept
{
	::glPopMatrix();
}
