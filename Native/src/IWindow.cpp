module;
#include "Internal.hpp"
#include <dwmapi.h>

module Glib.Windows.IWindow;
import Glib.Windows.Event.API;
import Glib.Windows.Context;
import Glib.Windows.Context.Renderer;

bool
gl::win32::IWindow::StartUpdate()
noexcept
{
	return 0 != Delegate(::UpdateWindow);
}

long long
gl::win32::IWindow::DefaultWndProc(const unsigned int& msg, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return Delegate(::DefWindowProc, msg, lhs, rhs);
}

bool
gl::win32::IWindow::Destroy()
noexcept
{
	if (handle_type& handle = GetHandle(); nullptr != handle)
	{
		if (bool result = (0 != Delegate(::DestroyWindow)); result)
		{
			handle = nullptr;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool
gl::win32::IWindow::SendCommand(const unsigned int& id, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return EventAPI::Push(GetHandle(), id, lhs, rhs);
}

bool
gl::win32::IWindow::SendCommand(const gl::win32::EventID& id, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return EventAPI::Push(GetHandle(), id, lhs, rhs);
}

bool
gl::win32::IWindow::SendCommand(const gl::win32::Event& cmd)
const noexcept
{
	return EventAPI::Push(GetHandle(), cmd);
}

bool
gl::win32::IWindow::SendCommand(gl::win32::Event&& cmd)
const noexcept
{
	return EventAPI::Push(GetHandle(), std::move(cmd));
}

bool
gl::win32::IWindow::SendCommand(const gl::win32::EventID& id, const gl::win32::io::KeyCode& keycode, const gl::win32::io::KeyboardFlag& flags)
const noexcept
{
	return SendCommand(id, static_cast<unsigned long long>(keycode), static_cast<long long>(flags));
}

bool
gl::win32::IWindow::UICommand(const int& cmd)
noexcept
{
	return 0 != Delegate(::ShowWindow, cmd);
}

bool
gl::win32::IWindow::Show()
noexcept
{
	return UICommand(SW_SHOW);
}

bool
gl::win32::IWindow::Hide()
noexcept
{
	return UICommand(SW_HIDE);
}

bool
gl::win32::IWindow::Maximize()
noexcept
{
	return UICommand(SW_MAXIMIZE);
}

bool
gl::win32::IWindow::Minimize()
noexcept
{
	return UICommand(SW_MINIMIZE);
}

bool
gl::win32::IWindow::Restore()
noexcept
{
	return UICommand(SW_RESTORE);
}

bool
gl::win32::IWindow::Clear(const Rect& rect)
noexcept
{
	RECT client{ rect.x, rect.y, rect.x + rect.w, rect.y + rect.h };

	return 0 != Delegate(::InvalidateRect, &client, FALSE);
}

bool
gl::win32::IWindow::Clear()
noexcept
{
	return 0 != Delegate(::InvalidateRect, nullptr, FALSE);
}

bool
gl::win32::IWindow::EnableRedraw(const bool& flag)
noexcept
{
	return SendCommand(EventID::SetRedraw, static_cast<WPARAM>(flag), 0);
}

bool
gl::win32::IWindow::Close()
noexcept
{
	return SendCommand(EventID::Close, 0, 0);
}

bool
gl::win32::IWindow::EnableInput()
noexcept
{
	return 0 != Delegate(::EnableWindow, TRUE);
}

bool
gl::win32::IWindow::DisableInput()
noexcept
{
	return 0 != Delegate(::EnableWindow, FALSE);
}

gl::win32::DeviceContext
gl::win32::IWindow::AcquireContext()
const noexcept
{
	return DeviceContext{ GetHandle() };
}

gl::win32::GraphicDeviceContext
gl::win32::IWindow::AcquireRenderContext()
const noexcept
{
	return GraphicDeviceContext{ GetHandle() };
}

bool
gl::win32::IWindow::ReleaseContext(gl::win32::DeviceContext& context)
const noexcept
{
	return 0 != Delegate(::ReleaseDC, context);
}

gl::win32::IContext
gl::win32::IWindow::AcquireNativeContext()
const noexcept
{
	return Delegate(::GetDC);
}

bool
gl::win32::IWindow::ReleaseNativeContext(gl::win32::IContext& context)
const noexcept
{
	return 0 != Delegate(::ReleaseDC, context);
}

bool
gl::win32::IWindow::IsMinimized()
const noexcept
{
	return 0 != Delegate(::IsIconic);
}

bool
gl::win32::IWindow::IsMaximized()
const noexcept
{
	return 0 != Delegate(::IsZoomed);
}

bool
gl::win32::IWindow::IsRestored()
const noexcept
{
	return 0L == (GetStyle() & (WS_MINIMIZE | WS_MAXIMIZE));
}

bool
gl::win32::IWindow::IsInputEnabled()
const noexcept
{
	return 0 != Delegate(::IsWindowEnabled);
}

long long
gl::win32::IWindow::SetInternalValue(int index, const long long& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, index, value);
}

long long
gl::win32::IWindow::SetInternalValue(int index, long long&& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, index, std::move(value));
}

long long
gl::win32::IWindow::SetInternalUserData(const long long& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, GWLP_USERDATA, value);
}

long long
gl::win32::IWindow::SetInternalUserData(long long&& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, GWLP_USERDATA, std::move(value));
}

long long
gl::win32::IWindow::GetInternalValue(int index)
const noexcept
{
	return Delegate(::GetWindowLongPtr, index);
}

long long
gl::win32::IWindow::GetInternalUserData()
const noexcept
{
	return GetInternalValue(GWLP_USERDATA);
}

unsigned long
gl::win32::IWindow::GetStyle()
const noexcept
{
	return static_cast<DWORD>(GetInternalValue(GWL_STYLE));
}

unsigned long
gl::win32::IWindow::GetExStyle()
const noexcept
{
	return static_cast<DWORD>(GetInternalValue(GWL_EXSTYLE));
}

int
gl::win32::IWindow::GetID()
const noexcept
{
	return static_cast<int>(GetInternalValue(GWLP_ID));
}

std::wstring
gl::win32::IWindow::GetTitle()
const noexcept
{
	std::wstring result{};
	result.reserve(64);

	Delegate(::GetWindowText, result.data(), static_cast<int>(result.size()));

	return result;
}

gl::Rect
gl::win32::IWindow::GetDimensions()
const noexcept
{
	native::NativeRect rect{};
	Delegate(::GetWindowRect, &rect);

	return gl::Rect
	{
		rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top
	};
}

bool
gl::win32::IWindow::TryGetDimensions(gl::Rect& output)
const noexcept
{
	native::NativeRect rect{};
	bool result = (0 != Delegate(::GetWindowRect, &rect));

	output = gl::Rect
	{
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top
	};

	return result;
}

gl::win32::IWindow
gl::win32::MakeNativeWindow(const ProcessInstance& hinst
	, const std::wstring_view& class_name
	, const std::wstring_view& title
	, const unsigned long& styles
	, const unsigned long& options
	, const int& x, const int& y
	, const int& width, const int& height
	, const gl::win32::IWindow& parent
	, const gl::win32::native::NativeMenu& menu
	, void* uparams
) noexcept
{
	gl::win32::native::HWND result = ::CreateWindowEx(options
	, class_name.data(), title.data()
	, styles, x, y, width, height
	, parent.GetHandle()
	, menu
	, hinst.myHandle, uparams);

	if (result == nullptr)
	{
		return nullptr;
	}

	const BOOL value = TRUE;
	if (auto hr = ::DwmSetWindowAttribute(result
		, DWMWA_USE_IMMERSIVE_DARK_MODE
		, &value, sizeof(value)); FAILED(hr))
	{
		::printf_s("DWMWA_USE_IMMERSIVE_DARK_MODE failed(%ld)\n", hr);
	}

	return IWindow{ std::move(result) };
}

void gl::win32::PostQuitMessage(const int& exit_code) noexcept
{
	::PostQuitMessage(exit_code);
}
