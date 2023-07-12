module;
#include "Internal.hpp"

module Glib.Device.Context.Renderer;

gl::device::GraphicDeviceContext::GraphicDeviceContext(const gl::device::native::HWND& handle)
noexcept
	: base(::BeginPaint(handle, &myStatus))
	, myWindowHandle(handle)
{}

gl::device::GraphicDeviceContext::~GraphicDeviceContext()
noexcept
{
	::EndPaint(myWindowHandle, &myStatus);
}

gl::device::native::PaintStruct&
gl::device::GraphicDeviceContext::GetPaintStruct()
noexcept
{
	return myStatus;
}

const gl::device::native::PaintStruct&
gl::device::GraphicDeviceContext::GetPaintStruct()
const noexcept
{
	return myStatus;
}
