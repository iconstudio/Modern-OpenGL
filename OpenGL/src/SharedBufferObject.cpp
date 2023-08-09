module;
module Glib;
import <memory>;
import :BufferObject;
import :SharedBufferObject;

void
gl::SharedBufferObject::Create(gl::buffer::BufferUsage usage, const size_t& bytes_size)
{
	myBlob = std::make_shared<float[]>(bytes_size);
}
