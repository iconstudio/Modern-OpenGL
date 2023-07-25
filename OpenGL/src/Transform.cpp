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

	::glFrustum;
	::glOrtho;

}

void
gl::transform::GetCurrentMatrix(TransformMode state, float(&matrix)[16])
noexcept
{
	::glGetFloatv(static_cast<GLenum>(state), matrix);
}

void
gl::transform::GetCurrentMatrix(TransformMode state, float* const& matrix)
noexcept
{
	::glGetFloatv(static_cast<GLenum>(state), matrix);
}

void
gl::transform::GetCurrentMatrix(TransformMode state, double(&matrix)[16])
noexcept
{
	::glGetDoublev(static_cast<GLenum>(state), matrix);
}

void
gl::transform::GetCurrentMatrix(TransformMode state, double* const& matrix)
noexcept
{
	::glGetDoublev(static_cast<GLenum>(state), matrix);
}
