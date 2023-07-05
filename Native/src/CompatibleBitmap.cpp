module;
#include "Internal.hpp"
module Glib.Device.Resource.CompatibleBitmap;

gl::device::resource::CompatibleBitmap::CompatibleBitmap(handle_type&& handle)
noexcept
	: base(std::move(handle))
{}

gl::device::resource::CompatibleBitmap::~CompatibleBitmap()
noexcept
{
	Destroy();
}
