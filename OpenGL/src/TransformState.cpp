module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :TransformState;

void
gl::transform::Push()
noexcept
{
	glPushMatrix();
}

void
gl::transform::Pop()
noexcept
{
	glPopMatrix();
}

void
gl::transform::SetMode(gl::TransformMode mode)
noexcept
{
	glMatrixMode(static_cast<GLenum>(mode));
}
