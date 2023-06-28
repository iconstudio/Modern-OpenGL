module;
#include "Internal.hpp"
#undef HIWORD

export module Glib.Device.IO.Keyboard.Flags;
import Glib.Device.Utility;

export namespace gl::device::io
{
	enum class KeyboardFlag : long long
	{
		None = 0,
		IsReleased = KF_UP,
		Previous = KF_REPEAT,
		IsAlt = KF_ALTDOWN,
		IsMenu = KF_MENUMODE,
		IsDialog = KF_DLGMODE,
		IsExtended = KF_EXTENDED,
	};

	[[nodiscard]]
	constexpr long long
		GetParam(const unsigned short& lparam_word, const io::KeyboardFlag& flag)
		noexcept
	{
		return static_cast<long long>(lparam_word) & static_cast<long long>(flag);
	}

	[[nodiscard]]
	constexpr long long
		GetParam(const long long& lparam, const io::KeyboardFlag& flag)
		noexcept
	{
		return GetParam(HIWORD(lparam), flag);
	}

	[[nodiscard]]
	constexpr long long
		GetParam(const unsigned long long& lparam, const io::KeyboardFlag& flag)
		noexcept
	{
		return GetParam(HIWORD(lparam), flag);
	}

	/// <summary>
	/// WM_KEYDOWN, WM_KEYUP, WM_CHAR, WM_DEADCHAR, WM_SYSKEYDOWN, WM_SYSKEYUP, WM_SYSCHAR, WM_SYSDEADCHAR
	/// </summary>
	[[nodiscard]]
	constexpr bool IsPressing(const long long& lparam) noexcept
	{
		return 0 == GetParam(lparam, io::KeyboardFlag::IsReleased);
	}

	/// <summary>
	/// WM_KEYDOWN, WM_KEYUP, WM_CHAR, WM_DEADCHAR, WM_SYSKEYDOWN, WM_SYSKEYUP, WM_SYSCHAR, WM_SYSDEADCHAR
	/// </summary>
	[[nodiscard]]
	constexpr bool IsFirstPress(const long long& lparam) noexcept
	{
		return 0 == GetParam(lparam, io::KeyboardFlag::Previous);
	}

	/// <summary>
	/// WM_SYSKEYDOWN, WM_SYSKEYUP, WM_SYSCHAR, WM_SYSDEADCHAR
	/// </summary>
	[[nodiscard]]
	constexpr bool IsWithAltKey(const long long& lparam) noexcept
	{
		return 0 != GetParam(lparam, io::KeyboardFlag::IsAlt);
	}
}
