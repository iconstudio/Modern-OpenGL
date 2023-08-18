module;
#define NOMINMAX
#include <Windows.h>
#include <gl\gl.h>

module Glib;
import :Primitive;

void
gl::global::EmitPrimitives(Primitive type, std::int32_t begin, std::uint32_t number)
noexcept
{
	::glDrawArrays(static_cast<GLenum>(type), begin, number)
}
