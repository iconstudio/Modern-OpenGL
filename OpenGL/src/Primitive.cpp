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

void
gl::draw::Vertex(int x, int y, int z)
noexcept
{
	::glVertex3i(x, y, z);
}

void
gl::draw::Vertex(float x, float y, float z)
noexcept
{
	::glVertex3f(x, y, z);
}

void
gl::draw::Vertex(double x, double y, double z)
noexcept
{
	::glVertex3d(x, y, z);
}

void
gl::draw::Vertex(std::span<int, 3> list)
noexcept
{
	::glVertex3iv(list.data());
}

void
gl::draw::Normal(int x, int y, int z)
noexcept
{
	::glNormal3i(x, y, z);
}

void
gl::draw::Normal(float x, float y, float z)
noexcept
{
	::glNormal3f(x, y, z);
}

void
gl::draw::Normal(double x, double y, double z)
noexcept
{
	::glNormal3d(x, y, z);
}

void
gl::draw::Normal(std::span<int, 3> list)
noexcept
{
	::glNormal3iv(list.data());
}

void
gl::draw::TexCoord(int s, int t)
noexcept
{
	::glTexCoord2i(s, t);
}

void
gl::draw::TexCoord(float s, float t)
noexcept
{
	::glTexCoord2f(s, t);
}

void
gl::draw::TexCoord(double s, double t)
noexcept
{
	::glTexCoord2d(s, t);
}

void
gl::draw::TexCoord(std::span<int, 2> list)
noexcept
{
	::glTexCoord2iv(list.data());
}

void
gl::draw::TexCoord(std::span<float, 2> list)
noexcept
{
	::glTexCoord2fv(list.data());
}

void
gl::draw::TexCoord(std::span<double, 2> list)
noexcept
{
	::glTexCoord2dv(list.data());
}

void
gl::draw::SetColour(const gl::Colour& color)
noexcept
{
	::glColor3ub(color.r, color.g, color.b);
}

void
gl::draw::SetColour(gl::Colour&& color)
noexcept
{
	::glColor3ub(color.r, color.g, color.b);
}

void
gl::draw::SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b)
noexcept
{
	::glColor3ub(r, g, b);
}

void
gl::draw::SetColour(int r, int g, int b)
noexcept
{
	::glColor3i(r, g, b);
}

void
gl::draw::SetColour(float ratio_r, float ratio_g, float ratio_b)
noexcept
{
	::glColor3f(ratio_r, ratio_g, ratio_b);
}

void
gl::draw::SetColour(double ratio_r, double ratio_g, double ratio_b)
noexcept
{
	::glColor3d(ratio_r, ratio_g, ratio_b);
}

void
gl::draw::SetColour(int r, int g, int b, int a)
noexcept
{
	::glColor4i(r, g, b, a);
}

void
gl::draw::SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
noexcept
{
	::glColor4ub(r, g, b, a);
}

void
gl::draw::SetColour(float ratio_r, float ratio_g, float ratio_b, float ratio_a)
noexcept
{
	::glColor4f(ratio_r, ratio_g, ratio_b, ratio_a);
}

void
gl::draw::SetColour(double ratio_r, double ratio_g, double ratio_b, double ratio_a)
noexcept
{
	::glColor4d(ratio_r, ratio_g, ratio_b, ratio_a);
}
