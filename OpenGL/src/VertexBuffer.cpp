module;
module Glib;
import <type_traits>;
import :VertexBuffer;

gl::VertexBuffer::VertexBuffer()
noexcept
	: base(buffer::BufferType::Array)
{}

void
gl::VertexBuffer::Create(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(list.begin(), list.size(), usage);
}

void
gl::VertexBuffer::Create(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(list.begin(), list.size(), usage);
}

void
gl::VertexBuffer::Create(std::initializer_list<float> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(list.begin(), list.size(), usage);
}
