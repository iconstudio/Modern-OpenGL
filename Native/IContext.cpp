module;
#include "Internal.hpp"
module Glib.Device.IContext;

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

constexpr
gl::device::IContext::operator
gl::device::native::NativeContext& ()
& noexcept
{
	return GetHandle();
}

constexpr
gl::device::IContext::operator
const gl::device::native::NativeContext& ()
const& noexcept
{
	return GetHandle();
}

constexpr
gl::device::IContext::operator
gl::device::native::NativeContext && ()
&& noexcept
{
	return std::move(GetHandle());
}

constexpr
gl::device::IContext::operator
const gl::device::native::NativeContext && ()
const&& noexcept
{
	return std::move(GetHandle());
}
