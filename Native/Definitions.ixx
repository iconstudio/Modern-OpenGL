module;
#include "Internal.hpp"

export module Glib.Device.Definitions;
import <filesystem>;

export namespace gl::device
{
	using FilePath = std::filesystem::path;
}

export namespace gl::device::native
{
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);
	using RawWindowProperty = ::tagWNDCLASSEXW;

	using NativeSurface = ::HDC__*;
	using RawBitmap = ::HBITMAP__*;
	using RawIcon = ::HICON__*;
	using RawColorBrush = ::HBRUSH__*;
	using RawPen = ::HPEN__*;
	using RawPalette = ::HPALETTE__*;
	using RawFont = ::HFONT__*;
}
