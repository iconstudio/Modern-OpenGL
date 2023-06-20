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
		, class_name, title
		, styles, x, y, width, height
		, parent
		, menu
		, hinst, uparams);
	}
}
