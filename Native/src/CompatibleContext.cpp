module;
#include "Internal.hpp"
module Glib.Device.CompatibleContext;

gl::device::CompatibleContext::~CompatibleContext()
noexcept
{
	Delegate(::DeleteDC);
}
