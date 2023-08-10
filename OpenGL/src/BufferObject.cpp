module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>

module Glib;
import <tuple>;
import :BufferObject;

using element_vector_t = decltype(std::declval<gl::BufferLayout>().GetElements());
void AttachElement(const element_vector_t& elements) noexcept;

gl::detail::BufferImplement::BufferImplement(gl::buffer::BufferType buffer_type)
noexcept
	: base()
	, myType(buffer_type), myUsage(buffer::BufferUsage::None)
	, myLayout(), mySize(0)
{
	::glGenBuffers(1, std::addressof(myID));
}

gl::detail::BufferImplement::~BufferImplement()
noexcept
{
	Destroy();
}

gl::BufferObject::BufferObject(gl::buffer::BufferType buffer_type)
noexcept
	: base(buffer_type)
{}

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
gl::detail::BufferImplement::Create(const void* const& data, const size_t& size, gl::buffer::BufferUsage usage)
noexcept
{
	Binder binder{ myType, myID };

	::glBufferData(binder.bftype, size, data, static_cast<GLenum>(usage));

	mySize = size;
	myUsage = usage;
}
void
gl::detail::BufferImplement::Destroy()
{
	::glDeleteBuffers(1, std::addressof(myID));
}

void
gl::detail::BufferImplement::CopyFrom(const void* const& src_data, const size_t& size, const ptrdiff_t& offset)
noexcept
{
	Binder binder{ myType, myID };

	::glBufferSubData(binder.bftype, offset, size, src_data);

	mySize = size;
}

void
gl::detail::BufferImplement::Bind()
const noexcept
{
	::glBindBuffer(static_cast<GLenum>(myType), myID);
}

void
gl::detail::BufferImplement::Unbind()
const noexcept
{
	::glBindBuffer(static_cast<GLenum>(myType), 0);
}

void
gl::detail::BufferImplement::Use()
const noexcept
{
	Bind();
	::AttachElement(myLayout.GetElements());
	Unbind();
}

void
gl::detail::BufferImplement::CopyTo(gl::detail::BufferImplement& other
	, const size_t& dest_size, const ptrdiff_t& dest_offset
	, const ptrdiff_t& offset)
	const noexcept
{
	::glBindBuffer(GL_COPY_READ_BUFFER, myID);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, other.myID);
	::glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, offset, dest_offset, dest_size);
	::glBindBuffer(GL_COPY_READ_BUFFER, 0);
	::glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

void
AttachElement(const element_vector_t& elements)
noexcept
{
	GLuint index = 0;
	for (auto& item : elements)
	{
		const int& count = std::get<0>(item);
		const int& type = std::get<1>(item);
		const int& stride = std::get<2>(item);
		const ptrdiff_t& offset = std::get<3>(item);
		const bool& normalized = std::get<4>(item);

		::glVertexAttribPointer(index, count, type, normalized, stride, reinterpret_cast<const void*>(offset));
		::glEnableVertexAttribArray(index++);
	}
}
