module;
#include "Internal.hpp"
export module Glib.Device.Definitions;

export namespace gl::device::native
{
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);
	using RawWindowProperty = ::tagWNDCLASSEXW;

	using NativeColorBrush = ::HBRUSH__*;
}
