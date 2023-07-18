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

	GL_ONE;
}

gl::Blender::Blender(const gl::BlendMode& mode)
noexcept
	: Blender(mode.srcOption, mode.dstOption)
{}

gl::Blender::Blender(gl::BlendMode&& mode)
noexcept
	: Blender(std::move(mode.srcOption), std::move(mode.dstOption))
{}

gl::Blender::Blender(gl::BlendOption src, gl::BlendOption dest)
noexcept
	: isBlending(true)
	, wasBlending(global::IsBlending())
{
	GLint prev_source = 0;
	::glGetIntegerv(GL_BLEND_SRC, &prev_source);
	prevSrcMode = static_cast<BlendOption>(prev_source);

	GLint prev_dest = 0;
	::glGetIntegerv(GL_BLEND_DST, &prev_dest);
	prevDstMode = static_cast<BlendOption>(prev_dest);

	mySrcMode = src;
	myDstMode = dest;
	Apply();

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

	if (BlendOption::Invalid != prevDstMode)
	{
		::glBlendFunc(static_cast<GLenum>(prevSrcMode), static_cast<GLenum>(prevDstMode));
	}
}

void
gl::Blender::Apply()
const noexcept
{
	if (BlendOption::Invalid != mySrcMode && BlendOption::Invalid != myDstMode)
	{
		::glBlendFunc(static_cast<GLenum>(mySrcMode), static_cast<GLenum>(myDstMode));
	}
}

bool
gl::Blender::IsBlending()
const noexcept
{
	return isBlending;
}

util::Monad<gl::BlendOption>
gl::Blender::GetSrcMode()
const noexcept
{
	if (BlendOption::Invalid != mySrcMode)
	{
		return mySrcMode;
	}
	else
	{
		return util::nullopt;
	}
}

util::Monad<gl::BlendOption>
gl::Blender::GetDstMode()
const noexcept
{
	if (BlendOption::Invalid != myDstMode)
	{
		return myDstMode;
	}
	else
	{
		return util::nullopt;
	}
}

util::Monad<gl::BlendOption>
gl::Blender::GetPrevSrcMode()
const noexcept
{
	if (BlendOption::Invalid != prevSrcMode)
	{
		return prevSrcMode;
	}
	else
	{
		return util::nullopt;
	}
}

util::Monad<gl::BlendOption>
gl::Blender::GetPrevDstMode()
const noexcept
{
	if (BlendOption::Invalid != prevDstMode)
	{
		return prevDstMode;
	}
	else
	{
		return util::nullopt;
	}
}

void
gl::Blender::swap(gl::Blender& other)
noexcept
{
	std::swap(isBlending, other.isBlending);
	std::swap(wasBlending, other.wasBlending);
	std::swap(mySrcMode, other.mySrcMode);
	std::swap(myDstMode, other.myDstMode);
	std::swap(prevSrcMode, other.prevSrcMode);
	std::swap(prevDstMode, other.prevDstMode);
}
