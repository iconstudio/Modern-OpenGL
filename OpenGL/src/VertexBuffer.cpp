module;

module Glib;
import :VertexBuffer;

gl::VertexBuffer::VertexBuffer()
noexcept
	: myHandle(buffer::BufferType::Array)
{}
