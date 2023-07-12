module;
#include "Internal.hpp"
module Glib.Device.CompatibleContext;

gl::win32::CompatibleContext::~CompatibleContext()
noexcept
{
	Delegate(::DeleteDC);
}
