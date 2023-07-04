module;
#include "Internal.hpp"
#include <dwmapi.h>
module Glib.Device.IWindowHandle;

HWND__* gl::device::MakeNativeWindow(const HINSTANCE& hinst, const std::wstring_view& class_name
	, const std::wstring_view& title
	, const unsigned long& styles
	, const unsigned long& options
	, const int& x, const int& y
	, const int& width, const int& height
	, const HWND& parent
	, const HMENU& menu
	, const LPVOID& uparams
) noexcept
{
	HWND result = ::CreateWindowEx(options
	, class_name.data(), title.data()
	, styles, x, y, width, height
	, parent
	, menu
	, hinst, uparams);

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

bool
gl::device::RegisterWindow(const gl::device::native::RawWindowProperty& property)
noexcept
{
	return 0 == ::RegisterClassEx(&property);
}

bool gl::device::UnregisterWindow(const HINSTANCE& hinst, const std::wstring_view& class_name)
{
	return 0 == ::UnregisterClass(class_name.data(), hinst);
}

void gl::device::PostQuitMessage(const int& exit_code) noexcept
{
	::PostQuitMessage(exit_code);
}
