module;
module Glib;
import <type_traits>;
import :IndexBuffer;

void
gl::IndexBuffer::Create(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage)
noexcept 
{
	base::Create(buffer::BufferType::ElementArray, usage, list.begin(), list.size());
}

void
gl::IndexBuffer::Create(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(buffer::BufferType::ElementArray, usage, list.begin(), list.size());
}
