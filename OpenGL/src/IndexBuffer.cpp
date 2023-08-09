module;
module Glib;
import <type_traits>;
import :IndexBuffer;

gl::IndexBuffer::IndexBuffer()
noexcept
	: myHandle(buffer::BufferType::ElementArray)
{}

void
gl::IndexBuffer::Assign(const void* const& data, const size_t& size, buffer::BufferUsage usage)
noexcept
{
	myHandle.SetData(data, size, usage);
}

void
gl::IndexBuffer::SetLayout(const BufferLayout & layout)
noexcept
{}

void
gl::IndexBuffer::SetLayout(BufferLayout && layout)
noexcept
{}

void
gl::IndexBuffer::Bind()
const noexcept
{}

void
gl::IndexBuffer::Unbind()
const noexcept
{}

void
gl::IndexBuffer::Use()
const noexcept
{}

gl::buffer::BufferUsage
gl::IndexBuffer::GetUsage()
const noexcept
{
	return buffer::BufferUsage();
}

size_t
gl::IndexBuffer::GetSize()
const noexcept
{
	return size_t();
}

gl::BufferObject&
gl::IndexBuffer::GetHandle()
noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
}

const gl::BufferObject&
gl::IndexBuffer::GetHandle()
const noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
}
