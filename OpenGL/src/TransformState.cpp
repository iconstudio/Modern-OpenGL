module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :TransformState;

void
gl::transform::SetState(gl::TransformMode mode)
noexcept
{
	glMatrixMode(static_cast<GLenum>(mode));
}

void
gl::transform::PushState()
noexcept
{
	glPushMatrix();
}

void
gl::transform::PopState()
noexcept
{
	glPopMatrix();
}
