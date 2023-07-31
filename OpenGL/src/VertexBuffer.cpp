module;
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glew.h>

module Glib;
import :VertexBuffer;

gl::VertexBuffer::VertexBuffer()
	: base()
{
	::glGenBuffers(1, &myID);
}

gl::VertexBuffer::~VertexBuffer()
{
	::glDeleteBuffers(1, &myID);
}

void

void
gl::VertexBuffer::CopyTo(VertexBuffer& other, size_t size, size_t srcOffset, size_t dstOffset)
const noexcept
{
	::glBindBuffer(GL_COPY_READ_BUFFER, myID);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, other.myID);
	::glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcOffset, dstOffset, size);
	::glBindBuffer(GL_COPY_READ_BUFFER, 0);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}
