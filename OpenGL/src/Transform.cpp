module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :Transform;

void
gl::transform::LoadIdentity()
noexcept
{
	::glLoadIdentity();
}
