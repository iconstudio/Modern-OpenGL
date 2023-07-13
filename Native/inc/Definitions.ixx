module;
#include "Internal.hpp"

export module Glib.Windows.Definitions;
import <filesystem>;

export namespace gl::win32
{
	using FilePath = std::filesystem::path;
}

export namespace gl::win32
{
	class ProcessInstance;
	class IContext;
	class DeviceContext;
	class CompatibleContext;
	class GraphicDeviceContext;
	class GlobalDeviceContext;
	class Colour;
	class IWindow;
}

export namespace gl::win32::resource
{
	class Image;
	class Bitmap;
	class Palette;
	class ColorBrush;
	class Pen;
	class CompatibleBitmap;
	class Icon;
}

export namespace gl::win32
{
	class Window;
	class ManagedWindow;
}

export namespace gl::win32::native
{
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);
	using RawWindowProperty = tagWNDCLASSEXW;
	using NativeRect = tagRECT;

	using HINSTANCE = HINSTANCE__*;
	using HWND = HWND__*;
	using PaintStruct = tagPAINTSTRUCT;
	using NativeContext = ::HDC__*;
	using NativeOGL = ::HGLRC__*;
	using NativeMenu = ::HMENU__*;

	using RawBitmap = ::HBITMAP__*;
	using RawIcon = ::HICON__*;
	using RawColorBrush = ::HBRUSH__*;
	using RawPen = ::HPEN__*;
	using RawPalette = ::HPALETTE__*;
	using RawFont = ::HFONT__*;
}
