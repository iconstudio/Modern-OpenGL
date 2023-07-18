module;
#include <Windows.h>
#include <gl\gl.h>
module Glib.Culling;

void
gl::Culling(Face face)
noexcept
{
	::glCullFace(static_cast<GLenum>(face));
}

void
gl::CullingDirection(bool clockwise)
noexcept
{
	::glFrontFace(clockwise ? GL_CW : GL_CCW);
}
