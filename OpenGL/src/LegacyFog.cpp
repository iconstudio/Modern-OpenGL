module;
#include <Windows.h>
#include <gl\gl.h>
#undef near
#undef far

module Glib.Legacy.Fog;
import <type_traits>;

void
InitFog(GLint mode, const float* const& colors, float density, float near, float far)
noexcept
{
	::glEnable(GL_FOG);
	::glFogi(GL_FOG_MODE, mode);
	::glFogfv(GL_FOG_COLOR, colors);
	::glFogf(GL_FOG_DENSITY, density);
	::glFogf(GL_FOG_START, near);
	::glFogf(GL_FOG_END, far);
}

gl::legacy::Fog::Fog(float near, float far, float density)
noexcept
	: myOperation(FogOperation::Exp1)
	, distNear(near), distFar(far), myDensity(density)
{
	myColor.Extract(cachedColor);

	InitFog(static_cast<GLint>(myOperation), cachedColor, myDensity, distNear, distFar);
}

gl::legacy::Fog::Fog(FogOperation operation, float near, float far, float density)
noexcept
	: myOperation(operation)
	, distNear(near), distFar(far), myDensity(density)
{
	myColor.Extract(cachedColor);

	InitFog(static_cast<GLint>(myOperation), cachedColor, myDensity, distNear, distFar);
}

gl::legacy::Fog::Fog(const Colour& color, float near, float far, float density)
noexcept
	: myOperation(FogOperation::Exp1)
	, distNear(near), distFar(far), myDensity(density)
	, myColor(color)
{
	myColor.Extract(cachedColor);

	InitFog(static_cast<GLint>(myOperation), cachedColor, myDensity, distNear, distFar);
}

gl::legacy::Fog::Fog(Colour&& color, float near, float far, float density)
noexcept
	: myOperation(FogOperation::Exp1)
	, distNear(near), distFar(far), myDensity(density)
	, myColor(std::move(color))
{
	myColor.Extract(cachedColor);

	InitFog(static_cast<GLint>(myOperation), cachedColor, myDensity, distNear, distFar);
}

gl::legacy::Fog::Fog(FogOperation operation, const gl::legacy::Colour& color, float near, float far, float density)
noexcept
	: myOperation(operation)
	, distNear(near), distFar(far), myDensity(density)
	, myColor(color)
{
	myColor.Extract(cachedColor);

	InitFog(static_cast<GLint>(myOperation), cachedColor, myDensity, distNear, distFar);
}

gl::legacy::Fog::Fog(FogOperation operation, gl::legacy::Colour&& color, float near, float far, float density)
noexcept
	: myOperation(operation)
	, distNear(near), distFar(far), myDensity(density)
	, myColor(std::move(color))
{
	myColor.Extract(cachedColor);

	InitFog(static_cast<GLint>(myOperation), cachedColor, myDensity, distNear, distFar);
}

gl::legacy::Fog::~Fog()
noexcept
{
	::glDisable(GL_FOG);
}

void
gl::legacy::Fog::Operation(gl::legacy::FogOperation operation)
noexcept
{
	myOperation = operation;
	::glFogi(GL_FOG_MODE, static_cast<GLint>(myOperation));
}

gl::legacy::FogOperation
gl::legacy::Fog::Operation()
const noexcept
{
	return myOperation;
}

void
gl::legacy::Fog::Color(const gl::legacy::Colour& color)
noexcept
{
	myColor = color;
	myColor.Extract(cachedColor);
	::glFogfv(GL_FOG_COLOR, cachedColor);
}

void gl::legacy::Fog::Color(gl::legacy::Colour&& color)
noexcept
{
	myColor = std::move(color);
	myColor.Extract(cachedColor);
	::glFogfv(GL_FOG_COLOR, cachedColor);
}

void
gl::legacy::Fog::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
noexcept
{
	myColor = Colour(r, g, b, a);
	myColor.Extract(cachedColor);
	::glFogfv(GL_FOG_COLOR, cachedColor);
}

void
gl::legacy::Fog::Color(float r, float g, float b, float a)
noexcept
{
	myColor = Colour(r, g, b, a);
	myColor.Extract(cachedColor);
	::glFogfv(GL_FOG_COLOR, cachedColor);
}

const gl::legacy::Colour&
gl::legacy::Fog::Color()
const noexcept
{
	return myColor;
}

void
gl::legacy::Fog::Density(float density)
noexcept
{
	myDensity = density;
}

float
gl::legacy::Fog::Density()
const noexcept
{
	return myDensity;
}

void
gl::legacy::Fog::NearDistance(float dist)
noexcept
{
	distNear = dist;
}

float
gl::legacy::Fog::NearDistance()
const noexcept
{
	return distNear;
}

void
gl::legacy::Fog::FarDistance(float dist)
noexcept
{
	distFar = dist;
}

float
gl::legacy::Fog::FarDistance()
const noexcept
{
	return distFar;
}
