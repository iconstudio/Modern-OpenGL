module;
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

module Glib;
import <tuple>;
import :BufferObject;

using element_vector_t = decltype(std::declval<gl::BufferLayout>().GetElements());

void
AttachElement(const element_vector_t& elements)
noexcept
{
	GLuint index = 0;
	for (auto& item : elements)
	{
		const int& count = std::get<0>(item);
		const int& type = std::get<1>(item);
		const bool& normalized = std::get<2>(item);
		const int& stride = std::get<3>(item);
		const ptrdiff_t& offset = std::get<4>(item);

		::glVertexAttribPointer(index, count, type, normalized, stride, reinterpret_cast<const void*>(offset));
		::glEnableVertexAttribArray(index++);
	}
}

gl::BufferObject::BufferObject()
	: base()
{
	::glGenBuffers(1, &myID);
}

gl::BufferObject::~BufferObject()
{
	::glDeleteBuffers(1, &myID);
}

struct Binder
{
	GLenum bftype;
	std::uint32_t id;

	Binder(gl::buffer::BufferType target, const std::uint32_t& id) noexcept
		: bftype(static_cast<GLenum>(target)), id(id)
	{
		::glBindBuffer(bftype, id);
	}

	~Binder() noexcept
	{
		::glBindBuffer(bftype, 0);
	}
};

void
gl::BufferObject::SetData(const void* const& data, const size_t& size, gl::buffer::BufferType usage)
noexcept
{
	Binder binder{ myType, myID };

	::glBufferData(binder.bftype, size, data, static_cast<GLenum>(usage));

	mySize = size;
	myType = usage;
}

void
gl::BufferObject::SetSubData(const void* const& src_data, const size_t& size, const ptrdiff_t& offset)
noexcept
{
	Binder binder{ myType, myID };

	::glBufferSubData(binder.bftype, offset, size, src_data);

	mySize = size;
}

void
gl::BufferObject::SetLayout(const gl::BufferLayout& layout)
noexcept
{
	Bind();
	::AttachElement(layout.GetElements());
	Unbind();

	myLayout = layout;
}

void
gl::BufferObject::SetLayout(BufferLayout&& layout)
noexcept
{
	myLayout = std::move(layout);

	Bind();
	::AttachElement(myLayout.GetElements());
	Unbind();
}

void
gl::BufferObject::Bind()
const noexcept
{
	::glBindBuffer(static_cast<GLenum>(myType), myID);
}

void
gl::BufferObject::Unbind()
const noexcept
{
	::glBindBuffer(static_cast<GLenum>(myType), 0);
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
gl::BufferObject::CopyTo(BufferObject& other
	, const size_t& dest_size, const ptrdiff_t& dest_offset = 0LL
	, const ptrdiff_t& offset)
const noexcept
{
	::glBindBuffer(GL_COPY_READ_BUFFER, myID);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, other.myID);
	::glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, offset, dest_offset, dest_size);
	::glBindBuffer(GL_COPY_READ_BUFFER, 0);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

gl::buffer::BufferType
gl::BufferObject::GetType()
const noexcept
{
	return myType;
}

const
gl::BufferLayout& gl::BufferObject::GetLayout()
const noexcept
{
	return myLayout;
}

size_t
gl::BufferObject::GetSize()
const noexcept
{
	return mySize;
}
