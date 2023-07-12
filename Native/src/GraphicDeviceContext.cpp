module;
#include "Internal.hpp"

module Glib.Windows.Context.Renderer;

gl::win32::GraphicDeviceContext::GraphicDeviceContext(const gl::win32::native::HWND& handle)
noexcept
	: base(::BeginPaint(handle, &myStatus))
	, myWindowHandle(handle)
{}

gl::win32::GraphicDeviceContext::~GraphicDeviceContext()
noexcept
{
	::EndPaint(myWindowHandle, &myStatus);
}

gl::win32::native::PaintStruct&
gl::win32::GraphicDeviceContext::GetPaintStruct()
noexcept
{
	return myStatus;
}

const gl::win32::native::PaintStruct&
gl::win32::GraphicDeviceContext::GetPaintStruct()
const noexcept
{
	return myStatus;
}
