module;
#include "Internal.hpp"
module Glib.Device.Context;

gl::device::DeviceContext::~DeviceContext()
noexcept
{
	Release(myWindowHandle);
}
