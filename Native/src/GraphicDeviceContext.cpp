module;
#include "Internal.hpp"
module Glib.Device.Context.Renderer;

gl::device::GraphicDeviceContext::GraphicDeviceContext(const gl::device::native::HWND& handle)
noexcept
	: base(::BeginPaint(handle, &myStatus))
	, myWindowHandle(handle)
	, myContext()
{
	myContext = ::wglCreateContext(myHandle);
}

gl::device::GraphicDeviceContext::~GraphicDeviceContext()
noexcept
{
	::EndPaint(myWindowHandle, &myStatus);

	if (myContext)
	{
		::wglDeleteContext(myContext);
	}
}

gl::device::native::PaintStruct&
gl::device::GraphicDeviceContext::GetStatus()
noexcept
{
	return myStatus;
}

const gl::device::native::PaintStruct&
gl::device::GraphicDeviceContext::GetStatus()
const noexcept
{
	return myStatus;
}
