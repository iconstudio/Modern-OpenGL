module;
#include "Internal.hpp"

export module Glib.Window:ABI;
import <string_view>;
import Glib.DefaultProperty;

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

	/// <summary>
	/// Only on the main thread
	/// </summary>
	void CaptureMouse(const HWND& handle) noexcept
	{
		::SetCapture(handle);
	}

	/// <summary>
	/// Only on the main thread
	/// </summary>
	[[nodiscard]]
	bool IsMouseCaptured(const HWND& handle) noexcept
	{
		return ::GetCapture() == handle;
	}

	/// <summary>
	/// Only on the main thread
	/// </summary>
	void ResetMouseCapture(const HWND& handle) noexcept
	{
		if (IsMouseCaptured(handle))
		{
			::ReleaseCapture();
		}
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

	inline long long DefaultWindowsProcedure(const HWND& hwnd, const unsigned int& msg, const unsigned long long& wparam, const long long& lparam) noexcept
	{
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
}
