module;
module Glib;
import <type_traits>;
import :IndexBuffer;

gl::IndexBuffer::IndexBuffer()
noexcept
	: base(buffer::BufferType::ElementArray)
{}

void
gl::IndexBuffer::Assign(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::SetData(list.begin(), list.size(), usage);
}

void
gl::IndexBuffer::Assign(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::SetData(list.begin(), list.size(), usage);
}
