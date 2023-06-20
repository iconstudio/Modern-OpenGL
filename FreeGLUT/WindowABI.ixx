module;
#include "Internal.hpp"

export module Glib.Device.Window:ABI;
import <string_view>;
import Glib.DefaultProperty;

export namespace gl::device
{
	using ::PVOID, ::LPVOID, ::WPARAM, ::LPARAM;
	using ::WNDPROC;
}

export namespace gl::device::detail
{
	using ::MSG, ::tagMSG;
	using RawDeviceMessage = ::tagMSG;

	[[nodiscard]]
	BOOL __GetMessage(const HWND& hwnd, RawDeviceMessage& msg) noexcept
	{
		return GetMessage(&msg, hwnd, 0, 0);
	}

	BOOL __TranslateMessage(const RawDeviceMessage& msg) noexcept
	{
		return TranslateMessage(&msg);
	}

	LRESULT __DispatchMessage(const RawDeviceMessage& msg) noexcept
	{
		return DispatchMessage(&msg);
	}

	inline void test_msg() noexcept
	{
		MSG Message;
		while (GetMessage(&Message, 0, 0, 0))
		{
			TranslateMessage(&Message);

			DispatchMessage(&Message);
		}
	}

	inline constexpr default_property_t<int> use_default = default_property_t{ CW_USEDEFAULT };

	inline bool RegisterProcess(const tagWNDCLASSEXW& property)
	{
		return 0 == ::RegisterClassEx(&property);
	}

	inline bool UnregisterProcess(const HINSTANCE& hinst, const std::wstring_view& class_name)
	{
		return 0 == ::UnregisterClass(class_name.data(), hinst);
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
		return 0 != ::DestroyWindow(hwnd);
	}
}
