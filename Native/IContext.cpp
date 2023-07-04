module;
#include "Internal.hpp"
module Glib.Device.IContext;

bool
gl::device::IContext::Destroy()
noexcept
{
	return false;
}

bool
gl::device::IContext::Release()
noexcept
{
	return false;
}

bool
gl::device::IContext::Release(gl::device::native::HWND& owner)
noexcept
{
	return false;
}
