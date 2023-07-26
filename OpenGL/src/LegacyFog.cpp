module;
#include <Windows.h>
#include <gl\gl.h>
#undef near
#undef far

module Glib.Legacy.Fog;
import <ranges>;

gl::legacy::Fog::Fog(float near, float far, float density)
noexcept
	: myOperation(FogOperation::Exp1)
	, myColor()
	, distNear(near), distFar(far), myDensity(density)
{
	// TODO: using std::views::enumerate

	size_t index = 0;
	for (float& color : cachedColor)
	{
		color = myColor[index++];
	}

	::glFogi(GL_FOG_MODE, static_cast<GLenum>(myOperation));
	::glFogfv(GL_FOG_COLOR, myColor);
	::glFogf(GL_FOG_DENSITY, myDensity);
	::glFogf(GL_FOG_START, distNear);
	::glFogf(GL_FOG_END, distFar);
}

gl::legacy::Fog::Fog(FogOperation operation, float near, float far, float density)
noexcept
{}

gl::legacy::Fog::Fog(const Colour& color, float near, float far, float density)
noexcept
{}

gl::legacy::Fog::Fog(Colour&& color, float near, float far, float density)
noexcept
{}

gl::legacy::Fog::Fog(FogOperation operation, const gl::legacy::Colour& color, float near, float far, float density)
noexcept
{}

gl::legacy::Fog::Fog(FogOperation operation, gl::legacy::Colour&& color, float near, float far, float density)
noexcept
{}

gl::legacy::Fog::~Fog()
noexcept
{}

void
gl::legacy::Fog::Operation(gl::legacy::FogOperation operation)
noexcept
{}

gl::legacy::FogOperation
gl::legacy::Fog::Operation()
const noexcept
{
	return FogOperation();
}

void
gl::legacy::Fog::Color(const gl::legacy::Colour& color)
noexcept
{}

void gl::legacy::Fog::Color(gl::legacy::Colour&& color)
noexcept
{}

void
gl::legacy::Fog::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
noexcept
{}

void
gl::legacy::Fog::Color(float r, float g, float b, float a)
noexcept
{}

const gl::legacy::Colour&
gl::legacy::Fog::Color()
const noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
}

void
gl::legacy::Fog::Density(float density)
noexcept
{}

float
gl::legacy::Fog::Density()
const noexcept
{
	return 0.0;
}

void
gl::legacy::Fog::NearDistance(float dist)
noexcept
{}

float
gl::legacy::Fog::NearDistance()
const noexcept
{
	return 0.0;
}

void
gl::legacy::Fog::FarDistance(float dist)
noexcept
{}

float
gl::legacy::Fog::FarDistance()
const noexcept
{
	return 0.0;
}
