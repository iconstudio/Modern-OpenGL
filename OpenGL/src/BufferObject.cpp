module;
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

module Glib;
import <tuple>;
import :BufferObject;

gl::BufferObject::BufferObject()
	: base()
{
	::glGenBuffers(1, &myID);
}

gl::BufferObject::~BufferObject()
{
	::glDeleteBuffers(1, &myID);
}

void
gl::BufferObject::SetData(const void* const& data, const size_t& size, gl::buffer::BufferType usage)
noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
	::glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(usage));
	::glBindBuffer(GL_ARRAY_BUFFER, 0);

	mySize = size;
	myType = usage;
}

void
gl::BufferObject::SetSubData(const void* const& src_data, const size_t& size, const size_t& offset)
noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
	::glBufferSubData(GL_ARRAY_BUFFER, offset, size, src_data);
	::glBindBuffer(GL_ARRAY_BUFFER, 0);

	mySize = size;
}

void
gl::BufferObject::SetLayout(const gl::BufferLayout& layout)
noexcept
{
	Bind();
	{

		const auto& elements = layout.GetElements();

		GLuint index = 0;
		for (auto& item : elements)
		{
			const int& count = std::get<0>(item);
			const int& type = std::get<1>(item);
			const bool& normalized = std::get<2>(item);
			const int& stride = std::get<3>(item);
			const int& offset = std::get<4>(item);

			::glVertexAttribPointer(index, count, type, normalized, stride, (void*)offset);
			::glEnableVertexAttribArray(index++);
		}
	}
	Unbind();
}

void
gl::BufferObject::Bind()
const noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
}

void
gl::BufferObject::Unbind()
const noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
gl::BufferObject::Use()
const noexcept
{
	::glBindBuffer(GL_ARRAY_BUFFER, myID);
	::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	::glEnableVertexAttribArray(0);
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
gl::BufferObject::CopyTo(BufferObject& other, size_t size, size_t srcOffset, size_t dstOffset)
const noexcept
{
	::glBindBuffer(GL_COPY_READ_BUFFER, myID);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, other.myID);
	::glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcOffset, dstOffset, size);
	::glBindBuffer(GL_COPY_READ_BUFFER, 0);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}
