module;
#include "Internal.hpp"
module Glib.Device.Resource.CompatibleBitmap;

gl::win32::resource::CompatibleBitmap::CompatibleBitmap(handle_type&& handle)
noexcept
	: base(std::move(handle))
{}

gl::win32::resource::CompatibleBitmap::~CompatibleBitmap()
noexcept
{
	Destroy();
}
