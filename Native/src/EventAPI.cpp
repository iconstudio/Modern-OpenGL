module;
#include "Internal.hpp"
module Glib.Windows.Event.API;

bool
gl::win32::EventAPI::Pop(const gl::win32::native::HWND& hwnd, gl::win32::RawEvent& output)
noexcept
{
	return 0 != ::GetMessage(&output, hwnd, 0, 0);
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, const unsigned int& id, const unsigned long long& lhs, const long long& rhs)
noexcept

{
	return 0 != ::PostMessage(hwnd, id, lhs, rhs);
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, unsigned int&& id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	return 0 != ::PostMessage(hwnd, std::move(id), lhs, rhs);
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, unsigned int&& id, unsigned long long&& lhs, long long&& rhs)
noexcept
{
	return 0 != ::PostMessage(hwnd, std::move(id), std::move(lhs), std::move(rhs));
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, const gl::win32::EventID& id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	return Push(hwnd, static_cast<unsigned int>(id), lhs, rhs);
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, gl::win32::EventID&& id, const unsigned long long& lhs, const long long& rhs)
noexcept
{
	return Push(hwnd, static_cast<unsigned int>(id), lhs, rhs);
}

bool
gl::win32::EventAPI::Push(const native::HWND& hwnd, gl::win32::EventID&& id, unsigned long long&& lhs, long long&& rhs)
noexcept
{
	return Push(hwnd, static_cast<unsigned int>(id), std::move(lhs), std::move(rhs));
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, const gl::win32::Event& msg)
noexcept
{
	return Push(hwnd, msg.id, msg.wParam, msg.lParam);
}

bool
gl::win32::EventAPI::Push(const gl::win32::native::HWND& hwnd, gl::win32::Event&& msg)
noexcept
{
	return Push(hwnd, std::move(msg.id), std::move(msg.wParam), std::move(msg.lParam));
}

bool
gl::win32::EventAPI::Peek(const gl::win32::native::HWND& hwnd, gl::win32::RawEvent& output, const gl::win32::EventPeeker& cmd)
noexcept
{
	return 0 != ::PeekMessage(std::addressof(output), hwnd, 0, 0, static_cast<unsigned int>(cmd));
}

long long
gl::win32::EventAPI::Dispatch(const gl::win32::RawEvent& msg)
noexcept
{
	return ::DispatchMessage(&msg);
}

bool
gl::win32::EventAPI::Translate(const RawEvent& msg)
noexcept
{
	return 0 != ::TranslateMessage(&msg);
}
