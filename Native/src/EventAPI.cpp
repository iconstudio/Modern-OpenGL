module;
#include "Internal.hpp"
module Glib.Device.Event.API;

bool
gl::device::EventAPI::Pop(const native::HWND& hwnd, gl::device::RawEvent& output)
noexcept
{
	return 0 != ::GetMessage(&output, hwnd, 0, 0);
}

bool
gl::device::EventAPI::Push(const native::HWND& hwnd, const unsigned int& id, const unsigned long long& lhs, const long long& rhs)
noexcept

{
	return 0 != ::PostMessage(hwnd, id, lhs, rhs);
}
