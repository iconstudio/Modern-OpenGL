module;
#include "Internal.hpp"
module Glib.Device.Event.API;

bool
gl::device::EventAPI::Pop(const gl::device::native::HWND& hwnd, gl::device::RawEvent& output)
noexcept
{
	return 0 != ::GetMessage(&output, hwnd, 0, 0);
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, const unsigned int& id, const unsigned long long& lhs, const long long& rhs)
noexcept

{
	return 0 != ::PostMessage(hwnd, id, lhs, rhs);
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, unsigned int&& id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	return 0 != ::PostMessage(hwnd, std::move(id), lhs, rhs);
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, unsigned int&& id, unsigned long long&& lhs, long long&& rhs)
noexcept
{
	return 0 != ::PostMessage(hwnd, std::move(id), std::move(lhs), std::move(rhs));
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, const gl::device::EventID& id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	return Push(hwnd, static_cast<unsigned int>(id), lhs, rhs);
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, gl::device::EventID&& id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	return Push(hwnd, static_cast<unsigned int>(id), lhs, rhs);
}

bool
gl::device::EventAPI::Push(const native::HWND& hwnd, gl::device::EventID&& id, unsigned long long&& lhs, long long&& rhs)
noexcept
{
	return Push(hwnd, static_cast<unsigned int>(id), std::move(lhs), std::move(rhs));
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, const gl::device::Event& msg)
noexcept
{
	return Push(hwnd, msg.id, msg.wParam, msg.lParam);
}

bool
gl::device::EventAPI::Push(const gl::device::native::HWND& hwnd, gl::device::Event&& msg)
noexcept
{
	return Push(hwnd, std::move(msg.id), std::move(msg.wParam), std::move(msg.lParam));
}

bool
gl::device::EventAPI::Peek(const gl::device::native::HWND& hwnd, gl::device::RawEvent& output, const gl::device::EventPeeker& cmd)
noexcept
{
	return 0 != ::PeekMessage(std::addressof(output), hwnd, 0, 0, static_cast<unsigned int>(cmd));
}

long long
gl::device::EventAPI::Dispatch(const gl::device::RawEvent& msg)
noexcept
{
	return ::DispatchMessage(&msg);
}

bool
gl::device::EventAPI::Translate(const RawEvent& msg)
noexcept
{
	return 0 != ::TranslateMessage(&msg);
}
