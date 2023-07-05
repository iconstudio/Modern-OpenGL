module;
#include "Internal.hpp"
#include <dwmapi.h>

module Glib.Device.IWindowHandle;
import Glib.Device.Event.API;
import Glib.Device.Context;
import Glib.Device.Context.Renderer;

bool
gl::device::IWindowHandle::StartUpdate()
noexcept
{
	return 0 != Delegate(::UpdateWindow);
}

long long
gl::device::IWindowHandle::DefaultWndProc(const unsigned int& msg, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return Delegate(::DefWindowProc, msg, lhs, rhs);
}

bool
gl::device::IWindowHandle::Destroy()
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
gl::device::IWindowHandle::SendCommand(const unsigned int& id, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return EventAPI::Push(GetHandle(), id, lhs, rhs);
}

bool
gl::device::IWindowHandle::SendCommand(const EventID& id, const unsigned long long& lhs, const long long& rhs)
const noexcept
{
	return EventAPI::Push(GetHandle(), id, lhs, rhs);
}

bool
gl::device::IWindowHandle::SendCommand(const Event& cmd)
const noexcept
{
	return EventAPI::Push(GetHandle(), cmd);
}

bool
gl::device::IWindowHandle::SendCommand(Event&& cmd)
const noexcept
{
	return EventAPI::Push(GetHandle(), static_cast<Event&&>(cmd));
}

bool
gl::device::IWindowHandle::SendCommand(const EventID& id, const io::KeyCode& keycode, const io::KeyboardFlag& flags)
const noexcept
{
	return SendCommand(id, static_cast<unsigned long long>(keycode), static_cast<long long>(flags));
}

bool
gl::device::IWindowHandle::UICommand(const int& cmd)
noexcept
{
	return 0 != Delegate(::ShowWindow, cmd);
}

bool
gl::device::IWindowHandle::Show()
noexcept
{
	return UICommand(SW_SHOW);
}

bool
gl::device::IWindowHandle::Hide()
noexcept
{
	return UICommand(SW_HIDE);
}

bool
gl::device::IWindowHandle::Maximize()
noexcept
{
	return UICommand(SW_MAXIMIZE);
}

bool
gl::device::IWindowHandle::Minimize()
noexcept
{
	return UICommand(SW_MINIMIZE);
}

bool
gl::device::IWindowHandle::Restore()
noexcept
{
	return UICommand(SW_RESTORE);
}

bool
gl::device::IWindowHandle::Redraw(const bool& flag)
noexcept
{
	return SendCommand(EventID::SetRedraw, static_cast<WPARAM>(flag), 0);
}

bool
gl::device::IWindowHandle::Close()
noexcept
{
	return SendCommand(EventID::Close, 0, 0);
}

bool
gl::device::IWindowHandle::EnableInput()
noexcept
{
	return 0 != Delegate(::EnableWindow, TRUE);
}

bool
gl::device::IWindowHandle::DisableInput()
noexcept
{
	return 0 != Delegate(::EnableWindow, FALSE);
}

gl::device::DeviceContext
gl::device::IWindowHandle::AcquireContext()
const noexcept
{
	return GetHandle();
}

gl::device::RenderingContext
gl::device::IWindowHandle::AcquireRenderContext()
const noexcept
{
	return RenderingContext{ GetHandle() };
}

bool
gl::device::IWindowHandle::ReleaseContext(gl::device::DeviceContext& context)
const noexcept
{
	return 0 != Delegate(::ReleaseDC, context);
}

gl::device::IContext
gl::device::IWindowHandle::AcquireNativeContext()
const noexcept
{
	return Delegate(::GetDC);
}

bool
gl::device::IWindowHandle::ReleaseNativeContext(IContext& context)
const noexcept
{
	return 0 != Delegate(::ReleaseDC, context);
}

bool
gl::device::IWindowHandle::IsMinimized()
const noexcept
{
	return 0 != Delegate(::IsIconic);
}

bool
gl::device::IWindowHandle::IsMaximized()
const noexcept
{
	return 0 != Delegate(::IsZoomed);
}

bool
gl::device::IWindowHandle::IsRestored()
const noexcept
{
	return 0L == (GetStyle() & (WS_MINIMIZE | WS_MAXIMIZE));
}

bool
gl::device::IWindowHandle::IsInputEnabled()
const noexcept
{
	return 0 != Delegate(::IsWindowEnabled);
}

long long
gl::device::IWindowHandle::SetInternalValue(int index, const long long& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, index, value);
}

long long
gl::device::IWindowHandle::SetInternalValue(int index, long long&& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, index, std::move(value));
}

long long
gl::device::IWindowHandle::SetInternalUserData(const long long& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, GWLP_USERDATA, value);
}

long long
gl::device::IWindowHandle::SetInternalUserData(long long&& value)
const noexcept
{
	return Delegate(::SetWindowLongPtr, GWLP_USERDATA, std::move(value));
}

long long
gl::device::IWindowHandle::GetInternalValue(int index)
const noexcept
{
	return Delegate(::GetWindowLongPtr, index);
}

long long
gl::device::IWindowHandle::GetInternalUserData()
const noexcept
{
	return GetInternalValue(GWLP_USERDATA);
}

unsigned long
gl::device::IWindowHandle::GetStyle()
const noexcept
{
	return static_cast<DWORD>(GetInternalValue(GWL_STYLE));
}

unsigned long
gl::device::IWindowHandle::GetExStyle()
const noexcept
{
	return static_cast<DWORD>(GetInternalValue(GWL_EXSTYLE));
}

int
gl::device::IWindowHandle::GetID()
const noexcept
{
	return static_cast<int>(GetInternalValue(GWLP_ID));
}

gl::device::native::NativeRect
gl::device::IWindowHandle::GetDimensions()
const noexcept
{
	native::NativeRect rect{};
	Delegate(::GetWindowRect, &rect);
	return rect;
}

bool
gl::device::IWindowHandle::TryGetDimensions(native::NativeRect& output)
const noexcept
{
	return 0 != Delegate(::GetWindowRect, &output);
}

HWND__*
gl::device::MakeNativeWindow(const ProcessInstance& hinst
	, const std::wstring_view& class_name
	, const std::wstring_view& title
	, const unsigned long& styles
	, const unsigned long& options
	, const int& x, const int& y
	, const int& width, const int& height
	, const HWND& parent
	, const HMENU& menu
	, void* uparams
) noexcept
{
	HWND result = ::CreateWindowEx(options
	, class_name.data(), title.data()
	, styles, x, y, width, height
	, parent
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

	return result;
}

bool gl::device::UnregisterWindow(const ProcessInstance& hinst, const std::wstring_view& class_name)
{
	return 0 == ::UnregisterClass(class_name.data(), hinst.myHandle);
}

void gl::device::PostQuitMessage(const int& exit_code) noexcept
{
	::PostQuitMessage(exit_code);
}
