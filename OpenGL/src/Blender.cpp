module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

module Glib.Blender;
import <utility>;
import Glib;

gl::Blender::Blender(bool enable)
noexcept
	: isBlending(enable)
	, wasBlending(global::IsBlending())
{
	if (isBlending && !wasBlending)
	{
		global::SetState(gl::State::Blending, true);
	}
	else if (!isBlending && wasBlending)
	{
		global::SetState(gl::State::Blending, false);
	}
}

gl::Blender::Blender(BlendMode src, BlendMode dest)
noexcept
	: isBlending(true)
	, wasBlending(global::IsBlending())
{
	GLint prev_source = 0;
	::glGetIntegerv(GL_BLEND_SRC, &prev_source);
	prevSrcMode = static_cast<BlendMode>(prev_source);

	GLint prev_dest = 0;
	::glGetIntegerv(GL_BLEND_DST, &prev_dest);
	prevDestMode = static_cast<BlendMode>(prev_dest);

	::glBlendFunc(static_cast<GLenum>(src), static_cast<GLenum>(dest));
	mySrcMode = src;
	myDestMode = dest;

	if (!wasBlending)
	{
		global::SetState(gl::State::Blending, true);
	}
}

gl::Blender::~Blender()
noexcept
{
	if (isBlending && !wasBlending)
	{
		global::SetState(gl::State::Blending, false);
	}
	else if (!isBlending && wasBlending)
	{
		global::SetState(gl::State::Blending, true);
	}

	if (BlendMode::None != prevDestMode)
	{
		::glBlendFunc(static_cast<GLenum>(prevSrcMode), static_cast<GLenum>(prevDestMode));
	}
}

void
gl::Blender::swap(gl::Blender& other)
noexcept
{
	std::swap(isBlending, other.isBlending);
	std::swap(wasBlending, other.wasBlending);
	std::swap(mySrcMode, other.mySrcMode);
	std::swap(myDestMode, other.myDestMode);
	std::swap(prevSrcMode, other.prevSrcMode);
	std::swap(prevDestMode, other.prevDestMode);
	std::swap(prevFunc, other.prevFunc);
}
