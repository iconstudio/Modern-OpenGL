module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
module Glib.Blender;

gl::Blender::Blender(bool enable)
noexcept
	: isBlending(enable)
	, wasBlending(gl::global::IsBlending())
{
	if (isBlending && !wasBlending)
	{
		::glEnable(GL_BLEND);
	}
	else if (!isBlending && wasBlending)
	{
		::glDisable(GL_BLEND);
	}
}

gl::Blender::Blender(BlendMode src, BlendMode dest)
noexcept
	: isBlending(true)
	, wasBlending(gl::global::IsBlending())
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
		::glEnable(GL_BLEND);
	}
}

gl::Blender::~Blender()
noexcept
{
	if (isBlending && !wasBlending)
	{
		::glDisable(GL_BLEND);
	}
	else if (!isBlending && wasBlending)
	{
		::glEnable(GL_BLEND);
	}
}
