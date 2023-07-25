module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#undef near
#undef far

module Glib;
import :Transform;

void
gl::transform::LoadIdentity()
noexcept
{
	::glLoadIdentity();
}

void
gl::transform::LookAt(float x, float y, float z, float tx, float ty, float tz, float ux, float uy, float uz)
noexcept
{
	::gluLookAt(double(x), double(y), double(z), double(tx), double(ty), double(tz), double(ux), double(uy), double(uz));
}

void
gl::transform::LookAt(double x, double y, double z, double tx, double ty, double tz, double ux, double uy, double uz)
noexcept
{
	::gluLookAt(x, y, z, tx, ty, tz, ux, uy, uz);
}

void
gl::transform::Projection(float fov, float aspect, float near, float far)
noexcept
{
	::gluPerspective(double(fov), double(aspect), double(near), double(far));
}

void
gl::transform::Projection(double fov, double aspect, double near, double far)
noexcept
{
	::gluPerspective(fov, aspect, near, far);
}

void
gl::transform::Ortho(float left, float right, float bottom, float top, float near, float far)
noexcept
{
	::glOrtho(double(left), double(right), double(bottom), double(top), double(near), double(far));
}

void
gl::transform::Ortho(double left, double right, double bottom, double top, double near, double far)
noexcept
{
	::glOrtho(left, right, bottom, top, near, far);
}

void
gl::transform::Translate(float x, float y, float z)
noexcept
{
	::glTranslatef(x, y, z);
}

void
gl::transform::Translate(double x, double y, double z)
noexcept
{
	::glTranslated(x, y, z);
}

void
gl::transform::Rotate(float angle, float x, float y, float z)
noexcept
{
	::glRotatef(angle, x, y, z);
}

void
gl::transform::Rotate(double angle, double x, double y, double z)
noexcept
{
	::glRotated(angle, x, y, z);
}

void
gl::transform::Scale(float x, float y, float z)
noexcept
{
	::glScalef(x, y, z);
}

void
gl::transform::Scale(double x, double y, double z)
noexcept
{
	::glScaled(x, y, z);
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
