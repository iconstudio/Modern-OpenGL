module;
#include "Internal.hpp"

export module Glib.Window:ABI;
import <string_view>;
import Glib.DefaultProperty;

export namespace gl::window
{
	using ::PVOID, ::LPVOID, ::WPARAM, ::LPARAM;
	using ::WNDPROC;

	using ::PostQuitMessage;
}

export namespace gl::window::detail
{
	inline constexpr default_property_t<int> use_default = default_property_t{ CW_USEDEFAULT };

	inline bool RegisterProcess(const tagWNDCLASSEXW& property)
	{
		return FALSE == ::RegisterClassEx(&property);
	}

	inline bool UnregisterProcess(const HINSTANCE& hinst, const std::wstring_view& class_name)
	{
		return FALSE == ::UnregisterClass(class_name.data(), hinst);
	}

	inline bool EnablePointingDevice() noexcept
	{
		return FALSE != ::EnableMouseInPointer(TRUE);
	}

	inline bool DisablePointingDevice() noexcept
	{
		return FALSE != ::EnableMouseInPointer(FALSE);
	}

	/// <summary>
	/// Is support pen or touch input?
	/// </summary>
	[[nodiscard]]
	inline bool IsPointingDeviceEnabled() noexcept
	{
		return FALSE != ::IsMouseInPointerEnabled();
	}

	[[nodiscard]]
	inline HWND__* CreateNativeWindow(const HINSTANCE& hinst
		, const std::wstring_view& class_name
		, const std::wstring_view& title
		, const unsigned long& styles
		, const unsigned long& options
		, const int& x
		, const int& y
		, const int& width
		, const int& height
		, const HWND& parent = nullptr
		, const HMENU& menu = nullptr
		, const LPVOID& uparams = nullptr)
		noexcept
	{
		return ::CreateWindowEx(options
		, class_name.data(), title.data()
		, styles, x, y, width, height
		, parent
		, menu
		, hinst, uparams);
	}

	inline bool DestroyNativeWindow(const HWND& hwnd) noexcept
	{
		return FALSE != ::DestroyWindow(hwnd);
	}
}
