module;
#include "Internal.hpp"
module Glib.Device.IContext;

gl::device::IContext
gl::device::IContext::CreateCompatibleContext()
const noexcept
{
	return Delegate(::CreateCompatibleDC);
}

gl::device::native::RawBitmap
gl::device::IContext::CreateCompatibleRawBitmap(const int& width, const int& height)
const noexcept
{
	return Delegate(::CreateCompatibleBitmap, width, height);
}

bool
gl::device::IContext::Destroy()
noexcept
{
	return 0 != Delegate(::DeleteDC);
}

bool
gl::device::IContext::Release()
noexcept
{
	return 0 != ::ReleaseDC(nullptr, GetHandle());
}

bool
gl::device::IContext::Release(gl::device::native::HWND& owner)
noexcept
{
	return 0 != ::ReleaseDC(owner, GetHandle());
}
