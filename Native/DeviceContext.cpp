module;
#include "Internal.hpp"
module Glib.Windows.Context;

gl::win32::DeviceContext::DeviceContext(const native::HWND& window)
noexcept
	: myWindowHandle(window)
	, base(::GetDC(window))
{}

gl::win32::DeviceContext::~DeviceContext()
noexcept
{
	Release(myWindowHandle);
}

gl::win32::GlobalDeviceContext::GlobalDeviceContext() noexcept
	: base(::GetDC(nullptr))
{}

gl::win32::GlobalDeviceContext::~GlobalDeviceContext() noexcept
{
	Release(nullptr);
}
