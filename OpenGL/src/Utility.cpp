module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :Utility;

void
gl::SetBackgroundColour(const gl::Colour& colour)
noexcept
{
	::glClearColor(colour.R / 255.0f, colour.G / 255.0f, colour.B / 255.0f, colour.A / 255.0f);
}

void
gl::SetBackgroundColour(gl::Colour&& colour)
noexcept
{
	::glClearColor(colour.R / 255.0f, colour.G / 255.0f, colour.B / 255.0f, colour.A / 255.0f);
}

void
gl::SetBackgroundColour(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b, const std::uint8_t& a)
noexcept
{
	::glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
