module;
#define NOMINMAX
#include <Windows.h>
#include <gl\gl.h>
module Glib.Legacy.Primitive;

gl::legacy::primitive::Context::Context(gl::Primitive mode)
noexcept
{
	::glBegin(static_cast<GLenum>(mode));
}

gl::legacy::primitive::Context::~Context()
noexcept
{
	::glEnd();
}

void
gl::legacy::primitive::Begin(gl::Primitive mode)
noexcept
{
	::glBegin(static_cast<GLenum>(mode));
}

void
gl::legacy::primitive::End()
noexcept
{
	::glEnd();
}

void
gl::legacy::primitive::Vertex(std::int32_t x, std::int32_t y, std::int32_t z)
noexcept
{
	::glVertex3i(x, y, z);
}

void
gl::legacy::primitive::Vertex(float x, float y, float z)
noexcept
{
	::glVertex3f(x, y, z);
}

void
gl::legacy::primitive::Vertex(double x, double y, double z)
noexcept
{
	::glVertex3d(x, y, z);
}

void
gl::legacy::primitive::Vertex(std::span<std::int32_t, 3> list)
noexcept
{
	::glVertex3iv(list.data());
}

void
gl::legacy::primitive::Normal(std::int32_t x, std::int32_t y, std::int32_t z)
noexcept
{
	::glNormal3i(x, y, z);
}

void
gl::legacy::primitive::Normal(float x, float y, float z)
noexcept
{
	::glNormal3f(x, y, z);
}

void
gl::legacy::primitive::Normal(double x, double y, double z)
noexcept
{
	::glNormal3d(x, y, z);
}

void
gl::legacy::primitive::Normal(std::span<std::int32_t, 3> list)
noexcept
{
	::glNormal3iv(list.data());
}

void
gl::legacy::primitive::TexCoord(std::int32_t s, std::int32_t t)
noexcept
{
	::glTexCoord2i(s, t);
}

void
gl::legacy::primitive::TexCoord(float s, float t)
noexcept
{
	::glTexCoord2f(s, t);
}

void
gl::legacy::primitive::TexCoord(double s, double t)
noexcept
{
	::glTexCoord2d(s, t);
}

void
gl::legacy::primitive::TexCoord(std::span<std::int32_t, 2> list)
noexcept
{
	::glTexCoord2iv(list.data());
}

void
gl::legacy::primitive::TexCoord(std::span<float, 2> list)
noexcept
{
	::glTexCoord2fv(list.data());
}

void
gl::legacy::primitive::TexCoord(std::span<double, 2> list)
noexcept
{
	::glTexCoord2dv(list.data());
}

void
gl::legacy::primitive::SetColour(const gl::Colour& color)
noexcept
{
	::glColor4ub(color.R, color.G, color.B, color.A);
}

void
gl::legacy::primitive::SetColour(gl::Colour&& color)
noexcept
{
	::glColor4ub(color.R, color.G, color.B, color.A);
}

void
gl::legacy::primitive::SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b)
noexcept
{
	::glColor3ub(r, g, b);
}

void
gl::legacy::primitive::SetColour(std::int32_t r, std::int32_t g, std::int32_t b)
noexcept
{
	::glColor3i(r, g, b);
}

void
gl::legacy::primitive::SetColour(float ratio_r, float ratio_g, float ratio_b)
noexcept
{
	::glColor3f(ratio_r, ratio_g, ratio_b);
}

void
gl::legacy::primitive::SetColour(double ratio_r, double ratio_g, double ratio_b)
noexcept
{
	::glColor3d(ratio_r, ratio_g, ratio_b);
}

void
gl::legacy::primitive::SetColour(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a)
noexcept
{
	::glColor4i(r, g, b, a);
}

void
gl::legacy::primitive::SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
noexcept
{
	::glColor4ub(r, g, b, a);
}

void
gl::legacy::primitive::SetColour(float ratio_r, float ratio_g, float ratio_b, float ratio_a)
noexcept
{
	::glColor4f(ratio_r, ratio_g, ratio_b, ratio_a);
}

void
gl::legacy::primitive::SetColour(double ratio_r, double ratio_g, double ratio_b, double ratio_a)
noexcept
{
	::glColor4d(ratio_r, ratio_g, ratio_b, ratio_a);
}
