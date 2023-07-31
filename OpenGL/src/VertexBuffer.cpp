module;
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glew.h>

module Glib;
import :VertexBuffer;

gl::VertexBuffer::VertexBuffer()
noexcept
	: base()
{
	::glGenBuffers(1, &myID);
}

gl::VertexBuffer::~VertexBuffer()
noexcept
{
	::glDeleteBuffers(1, &myID);
}
