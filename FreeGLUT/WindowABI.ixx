module;
#include "Internal.hpp"

export module Glib.Device.Window:ABI;
export import :Property;

export namespace gl::device::detail
{
	using ::HWND, ::HMENU, ::PVOID, ::LPVOID;

	[[nodiscard]]
	inline HWND CreateNativeWindow(const HINSTANCE& hinst
		, _Notnull_ const wchar_t* const& class_name
		, _Notnull_ const wchar_t* const& title
		, const unsigned long& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
		, const HWND& parent = nullptr
		, const HMENU& menu = nullptr
		, const LPVOID& uparams = nullptr)
		noexcept
	{
		return ::CreateWindowEx(0
		, class_name, title
		, style, x, y, width, height
		, parent
		, menu
		, hinst, uparams);
	}
}
