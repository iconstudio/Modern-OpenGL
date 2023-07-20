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
	prevMove.srcOption = static_cast<BlendOption>(prev_source);

	GLint prev_dest = 0;
	::glGetIntegerv(GL_BLEND_DST, &prev_dest);
	prevMove.dstOption = static_cast<BlendOption>(prev_dest);

	myMode.srcOption = src;
	myMode.dstOption = dest;
	Apply();
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

	if (BlendOption::Invalid != prevMove.dstOption)
	{
		::glBlendFunc(static_cast<GLenum>(prevMove.srcOption), static_cast<GLenum>(prevMove.dstOption));
	}
}

void
gl::Blender::Apply()
const noexcept
{
	if (BlendOption::Invalid != myMode.srcOption && BlendOption::Invalid != myMode.dstOption)
	{
		global::SetState(gl::State::Blending);
		::glBlendFunc(static_cast<GLenum>(myMode.srcOption), static_cast<GLenum>(myMode.dstOption));
	}
	else
	{
		global::SetState(gl::State::Blending, isBlending);
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
	if (BlendOption::Invalid != myMode.srcOption)
	{
		return myMode.srcOption;
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
	if (BlendOption::Invalid != myMode.dstOption)
	{
		return myMode.dstOption;
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
	if (BlendOption::Invalid != prevMove.srcOption)
	{
		return prevMove.srcOption;
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
	if (BlendOption::Invalid != prevMove.dstOption)
	{
		return prevMove.dstOption;
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
	std::swap(myMode.srcOption, other.myMode.srcOption);
	std::swap(myMode.dstOption, other.myMode.dstOption);
	std::swap(prevMove.srcOption, other.prevMove.srcOption);
	std::swap(prevMove.dstOption, other.prevMove.dstOption);
}
