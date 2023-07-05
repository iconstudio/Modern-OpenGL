module;
#include "Internal.hpp"
module Glib.Device.IContext;
import Glib.Device.CompatibleContext;
import Glib.Device.Resource.CompatibleBitmap;

gl::device::IContext::~IContext() noexcept
{
	if (shouldDestroy && nullptr != GetHandle())
	{
		Destroy();
	}
}

gl::device::CompatibleContext
gl::device::IContext::CreateCompatibleContext()
const noexcept
{
	return Delegate(::CreateCompatibleDC);
}

gl::device::resource::CompatibleBitmap
gl::device::IContext::CreateCompatibleBitmap(const int& width, const int& height)
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
