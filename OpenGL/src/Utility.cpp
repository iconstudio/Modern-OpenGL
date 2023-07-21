module;
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import <type_traits>;
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

void
gl::global::Clear(Clearance target)
noexcept
{
	::glClear(static_cast<GLbitfield>(target));
}

void
gl::global::SetViewport(const std::int32_t& x, const std::int32_t& y, const std::uint32_t& width, const std::uint32_t& height)
noexcept
{
	::glViewport(x, y, width, height);
}

void
gl::global::SetViewport(std::int32_t&& x, std::int32_t&& y, std::uint32_t&& width, std::uint32_t&& height)
noexcept
{
	::glViewport(std::move(x), std::move(y), std::move(width), std::move(height));
}

bool
gl::global::IsBlending()
noexcept
{
	GLboolean result{};
	::glGetBooleanv(GL_BLEND, &result);

	return GL_TRUE == result;
}

bool
gl::global::IsCulling()
noexcept
{
	GLboolean result{};
	::glGetBooleanv(GL_CULL_FACE, &result);

	return GL_TRUE == result;
}

bool
gl::global::IsScissoring()
noexcept
{
	GLboolean result{};
	::glGetBooleanv(GL_SCISSOR_TEST, &result);

	return GL_TRUE == result;
}

bool
gl::global::IsTestingAlpha()
noexcept
{
	GLboolean result{};
	::glGetBooleanv(GL_ALPHA, &result);

	return GL_TRUE == result;
}

bool
gl::global::IsTestingDepth()
noexcept
{
	GLboolean result{};
	::glGetBooleanv(GL_DEPTH_TEST, &result);

	return GL_TRUE == result;
}

bool
gl::global::IsTestingStencil()
noexcept
{
	GLboolean result{};
	::glGetBooleanv(GL_STENCIL_TEST, &result);

	return GL_TRUE == result;
}
