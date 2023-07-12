module;
#include "Internal.hpp"
#include <dwmapi.h>

module Glib.Device.IWindow;
import Glib.Device.Event.API;
import Glib.Device.Context;
import Glib.Device.Context.Renderer;

bool
gl::device::IWindow::StartUpdate()
noexcept
{
	return 0 != Delegate(::UpdateWindow);
}

long long
gl::device::IWindow::DefaultWndProc(const unsigned int& msg, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return Delegate(::DefWindowProc, msg, lhs, rhs);
}

bool
gl::device::IWindow::Destroy()
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
gl::device::IWindow::SendCommand(const unsigned int& id, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return EventAPI::Push(GetHandle(), id, lhs, rhs);
}

bool
gl::device::IWindow::SendCommand(const gl::device::EventID& id, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return EventAPI::Push(GetHandle(), id, lhs, rhs);
}

bool
gl::device::IWindow::SendCommand(const gl::device::Event& cmd)
const noexcept
{
	return EventAPI::Push(GetHandle(), cmd);
}

bool
gl::device::IWindow::SendCommand(gl::device::Event&& cmd)
const noexcept
{
	return EventAPI::Push(GetHandle(), std::move(cmd));
}

bool
gl::device::IWindow::SendCommand(const gl::device::EventID& id, const gl::device::io::KeyCode& keycode, const gl::device::io::KeyboardFlag& flags)
const noexcept
{
	return SendCommand(id, static_cast<unsigned long long>(keycode), static_cast<long long>(flags));
}

bool
gl::device::IWindow::UICommand(const int& cmd)
noexcept
{
	return 0 != Delegate(::ShowWindow, cmd);
}

bool
gl::device::IWindow::Show()
noexcept
{
	return UICommand(SW_SHOW);
}

bool
gl::device::IWindow::Hide()
noexcept
{
	return UICommand(SW_HIDE);
}

bool
gl::device::IWindow::Maximize()
noexcept
{
	return UICommand(SW_MAXIMIZE);
}

bool
gl::device::IWindow::Minimize()
noexcept
{
	return UICommand(SW_MINIMIZE);
}

bool
gl::device::IWindow::Restore()
noexcept
{
	return UICommand(SW_RESTORE);
}

bool
gl::device::IWindow::Clear(const Rect& rect)
noexcept
{
	RECT client{ rect.x, rect.y, rect.x + rect.w, rect.y + rect.h };

	return 0 != Delegate(::InvalidateRect, &client, TRUE);
}

bool
gl::device::IWindow::Clear()
noexcept
{
	return 0 != Delegate(::InvalidateRect, nullptr, TRUE);
}

bool
gl::device::IWindow::Redraw(const bool& flag)
noexcept
{
	return SendCommand(EventID::SetRedraw, static_cast<WPARAM>(flag), 0);
}

bool
gl::device::IWindow::Close()
noexcept
{
	return SendCommand(EventID::Close, 0, 0);
}

bool
gl::device::IWindow::EnableInput()
noexcept
{
	return 0 != Delegate(::EnableWindow, TRUE);
}

bool
gl::device::IWindow::DisableInput()
noexcept
{
	return 0 != Delegate(::EnableWindow, FALSE);
}

gl::device::DeviceContext
gl::device::IWindow::AcquireContext()
const noexcept
{
	return DeviceContext{ GetHandle() };
}

gl::device::GraphicDeviceContext
gl::device::IWindow::AcquireRenderContext()
const noexcept
{
	return GraphicDeviceContext{ GetHandle() };
}

bool
gl::device::IWindow::ReleaseContext(gl::device::DeviceContext& context)
const noexcept
{
	return 0 != Delegate(::ReleaseDC, context);
}

gl::device::IContext
gl::device::IWindow::AcquireNativeContext()
const noexcept
{
	return Delegate(::GetDC);
}

bool
gl::device::IWindow::ReleaseNativeContext(gl::device::IContext& context)
const noexcept
{
	return 0 != Delegate(::ReleaseDC, context);
}

bool
gl::device::IWindow::IsMinimized()
const noexcept
{
	return 0 != Delegate(::IsIconic);
}

bool
gl::device::IWindow::IsMaximized()
const noexcept
{
	return 0 != Delegate(::IsZoomed);
}

bool
gl::device::IWindow::IsRestored()
const noexcept
{
	return 0L == (GetStyle() & (WS_MINIMIZE | WS_MAXIMIZE));
}

bool
gl::device::IWindow::IsInputEnabled()
const noexcept
{
	return 0 != Delegate(::IsWindowEnabled);
}

long long
gl::device::IWindow::SetInternalValue(int index, const long long& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, index, value);
}

long long
gl::device::IWindow::SetInternalValue(int index, long long&& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, index, std::move(value));
}

long long
gl::device::IWindow::SetInternalUserData(const long long& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, GWLP_USERDATA, value);
}

long long
gl::device::IWindow::SetInternalUserData(long long&& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, GWLP_USERDATA, std::move(value));
}

long long
gl::device::IWindow::GetInternalValue(int index)
const noexcept
{
	return Delegate(::GetWindowLongPtr, index);
}

long long
gl::device::IWindow::GetInternalUserData()
const noexcept
{
	return GetInternalValue(GWLP_USERDATA);
}

unsigned long
gl::device::IWindow::GetStyle()
const noexcept
{
	return static_cast<DWORD>(GetInternalValue(GWL_STYLE));
}

unsigned long
gl::device::IWindow::GetExStyle()
const noexcept
{
	return static_cast<DWORD>(GetInternalValue(GWL_EXSTYLE));
}

int
gl::device::IWindow::GetID()
const noexcept
{
	return static_cast<int>(GetInternalValue(GWLP_ID));
}

std::wstring
gl::device::IWindow::GetTitle()
const noexcept
{
	std::wstring result{};
	result.reserve(64);

	Delegate(::GetWindowText, result.data(), static_cast<int>(result.size()));

	return result;
}

gl::Rect
gl::device::IWindow::GetDimensions()
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
gl::device::IWindow::TryGetDimensions(gl::Rect& output)
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

gl::device::IWindow
gl::device::MakeNativeWindow(const ProcessInstance& hinst
	, const std::wstring_view& class_name
	, const std::wstring_view& title
	, const unsigned long& styles
	, const unsigned long& options
	, const int& x, const int& y
	, const int& width, const int& height
	, const gl::device::IWindow& parent
	, const gl::device::native::NativeMenu& menu
	, void* uparams
) noexcept
{
	gl::device::native::HWND result = ::CreateWindowEx(options
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

void gl::device::PostQuitMessage(const int& exit_code) noexcept
{
	::PostQuitMessage(exit_code);
}
