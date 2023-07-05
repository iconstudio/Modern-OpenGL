module;
#include "Internal.hpp"
module Glib.Device.Context;

gl::device::DeviceContext::DeviceContext(const native::HWND& window)
noexcept
	: myWindowHandle(window)
	, base(::GetDC(window))
{}

gl::device::DeviceContext::~DeviceContext()
noexcept
{
	Release(myWindowHandle);
}

gl::device::GlobalDeviceContext::GlobalDeviceContext()
noexcept
	: myContext((native::HWND)(nullptr))
{}

gl::device::GlobalDeviceContext::~GlobalDeviceContext()
noexcept
{
	myContext.Release();
}
