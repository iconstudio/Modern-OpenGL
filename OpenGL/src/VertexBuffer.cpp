module;
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

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
gl::VertexBuffer::SetData(const void* const& data, const size_t& size, gl::buffer::BufferType usage)
noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
	::glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(usage));
	::glBindBuffer(GL_ARRAY_BUFFER, 0);

	mySize = size;
	myType = usage;
}

void
gl::VertexBuffer::SetSubData(const void* const& src_data, const size_t& size, const size_t& offset)
noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
	::glBufferSubData(GL_ARRAY_BUFFER, offset, size, src_data);
	::glBindBuffer(GL_ARRAY_BUFFER, 0);

	mySize = size;
}

void
gl::VertexBuffer::SetLayout(const int& layout)
noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
	::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, layout, (void*)0);
	::glEnableVertexAttribArray(0);
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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
