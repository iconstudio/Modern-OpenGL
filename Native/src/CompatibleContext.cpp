module;
#include "Internal.hpp"
module Glib.Windows.CompatibleContext;

gl::win32::CompatibleContext::~CompatibleContext()
noexcept
{
	Delegate(::DeleteDC);
}
