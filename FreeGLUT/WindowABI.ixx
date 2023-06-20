module;
#include "Internal.hpp"

export module Glib.Device.Window:ABI;
import <string_view>;
import Glib.DefaultProperty;
export import :Property;

export namespace gl::device::detail
{
	using Message = ::MSG;
	using ::HWND, ::HMENU, ::PVOID, ::LPVOID;

	inline constexpr default_property_t<int> use_default = default_property_t{ CW_USEDEFAULT };

	[[nodiscard]]
	inline HWND CreateNativeWindow(const HINSTANCE& hinst
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

	inline bool DestroyNativeWindow(HWND)
	{

	}
}
