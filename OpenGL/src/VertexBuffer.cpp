module;
module Glib;
import <type_traits>;
import :VertexBuffer;

gl::VertexBuffer::VertexBuffer()
noexcept
	: myHandle(buffer::BufferType::Array)
{}

void
gl::VertexBuffer::SetLayout(const BufferLayout& layout)
noexcept
{
	myHandle.SetLayout(layout);
}

void
gl::VertexBuffer::SetLayout(BufferLayout&& layout)
noexcept
{
	myHandle.SetLayout(std::move(layout));
}

void
gl::VertexBuffer::Bind()
const noexcept
{
	myHandle.Bind();
}

void
gl::VertexBuffer::Unbind()
const noexcept
{
	myHandle.Unbind();
}

void
gl::VertexBuffer::Use()
const noexcept
{
	myHandle.Use();
}

gl::buffer::BufferUsage
gl::VertexBuffer::GetUsage()
const noexcept
{
	return myHandle.GetUsage();
}

size_t
gl::VertexBuffer::GetSize()
const noexcept
{
	return myHandle.GetSize();

}

gl::BufferObject&
gl::VertexBuffer::GetHandle()
noexcept
{
	return myHandle;
}

const gl::BufferObject&
gl::VertexBuffer::GetHandle()
const noexcept
{
	return myHandle;
}
