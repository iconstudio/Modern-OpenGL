module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :Utility;

void
gl::global::SetState(const gl::State& state)
noexcept
{
	::glEnable(static_cast<GLenum>(state));
}

void
gl::global::SetState(gl::State&& state)
noexcept
{
	::glEnable(static_cast<GLenum>(state));
}

void
gl::global::SetState(const volatile gl::State& state)
noexcept
{
	::glEnable(static_cast<GLenum>(state));
}

void
gl::global::SetState(volatile gl::State&& state)
noexcept
{
	::glEnable(static_cast<GLenum>(state));
}

void
gl::global::SetState(const gl::State& state, bool flag)
noexcept
{
	if (flag)
	{
		::glEnable(static_cast<GLenum>(state));
	}
	else
	{
		::glDisable(static_cast<GLenum>(state));
	}
}

void
gl::global::SetState(const volatile gl::State& state, bool flag)
noexcept
{
	if (flag)
	{
		::glEnable(static_cast<GLenum>(state));
	}
	else
	{
		::glDisable(static_cast<GLenum>(state));
	}
}

void
gl::global::SetState(gl::State&& state, bool flag)
noexcept
{
	if (flag)
	{
		::glEnable(static_cast<GLenum>(state));
	}
	else
	{
		::glDisable(static_cast<GLenum>(state));
	}
}

void
gl::global::SetState(volatile gl::State&& state, bool flag)
noexcept
{
	if (flag)
	{
		::glEnable(static_cast<GLenum>(state));
	}
	else
	{
		::glDisable(static_cast<GLenum>(state));
	}
}

void
gl::global::SetBackgroundColour(const gl::Colour& colour)
noexcept
{
	::glClearColor(colour.R / 255.0f, colour.G / 255.0f, colour.B / 255.0f, colour.A / 255.0f);
}

void
gl::global::SetBackgroundColour(gl::Colour&& colour)
noexcept
{
	::glClearColor(colour.R / 255.0f, colour.G / 255.0f, colour.B / 255.0f, colour.A / 255.0f);
}

void
gl::global::SetBackgroundColour(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b, const std::uint8_t& a)
noexcept
{
	::glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
