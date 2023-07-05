module;
#include "Internal.hpp"

module Glib.Device.Context.Renderer;
import Glib.Device.IWindowHandle;

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
