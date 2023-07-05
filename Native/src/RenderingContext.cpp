module;
#include "Internal.hpp"
module Glib.Device.Context.Renderer;

gl::device::RenderingContext::RenderingContext(const gl::device::native::HWND& handle)
noexcept
	: base(::BeginPaint(handle, &myStatus))
	, myWindowHandle(handle)
{}

gl::device::RenderingContext::~RenderingContext()
noexcept
{
	::EndPaint(myWindowHandle, &myStatus);
}

gl::device::native::PaintStruct&
gl::device::RenderingContext::GetStatus()
noexcept
{
	return myStatus;
}

const gl::device::native::PaintStruct&
gl::device::RenderingContext::GetStatus()
const noexcept
{
	return myStatus;
}
