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
gl::IndexBuffer::SetLayout(const BufferLayout& layout)
noexcept
{
	myHandle.SetLayout(layout);
}

void
gl::IndexBuffer::SetLayout(BufferLayout&& layout)
noexcept
{
	myHandle.SetLayout(std::move(layout));
}

void
gl::IndexBuffer::Bind()
const noexcept
{
	myHandle.Bind();
}

void
gl::IndexBuffer::Unbind()
const noexcept
{
	myHandle.Unbind();
}

void
gl::IndexBuffer::Use()
const noexcept
{
	myHandle.Unbind();
}

gl::buffer::BufferUsage
gl::IndexBuffer::GetUsage()
const noexcept
{
	return myHandle.GetUsage();
}

size_t
gl::IndexBuffer::GetSize()
const noexcept
{
	return myHandle.GetSize();
}

gl::BufferObject&
gl::IndexBuffer::GetHandle()
noexcept
{
	return myHandle;
}

const gl::BufferObject&
gl::IndexBuffer::GetHandle()
const noexcept
{
	return myHandle;
}
