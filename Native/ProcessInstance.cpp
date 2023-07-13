module;
#include "Internal.hpp"
module Glib.Windows.ProcessInstance;

gl::win32::ProcessInstance
gl::win32::GetProcessInstance() noexcept
{
	return ProcessInstance{ ::GetModuleHandle(NULL) };
}
