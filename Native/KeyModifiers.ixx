module;
#include <windows.system.h>
export module Glib.Device.IO.Keyboard:Modifier;

using enum ABI::Windows::System::VirtualKeyModifiers;

export namespace gl::win32::io
{
	/// <summary>
	/// glutGetModifiers
	/// </summary>
	enum class [[nodiscard]] KeyModifiers : unsigned int
	{
		None = VirtualKeyModifiers_None,
		Shift = VirtualKeyModifiers_Shift,
		Ctrl = VirtualKeyModifiers_Control,
		Alt = VirtualKeyModifiers_Menu,
		Sys = VirtualKeyModifiers_Windows,
	};

	inline constexpr KeyModifiers Shift = KeyModifiers::Shift;
	inline constexpr KeyModifiers Ctrl = KeyModifiers::Ctrl;
	inline constexpr KeyModifiers Alt = KeyModifiers::Alt;
	inline constexpr KeyModifiers Sys = KeyModifiers::Sys;

	[[nodiscard]]
	constexpr KeyModifiers operator|(const KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		return static_cast<KeyModifiers>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers operator&(const KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		return static_cast<KeyModifiers>(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers operator^(const KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		return static_cast<KeyModifiers>(static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers operator~(const KeyModifiers& lhs) noexcept
	{
		return static_cast<KeyModifiers>(~static_cast<unsigned int>(lhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers& operator|=(KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		lhs = static_cast<KeyModifiers>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
		return lhs;
	}

	[[nodiscard]]
	constexpr KeyModifiers& operator&=(KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		lhs = static_cast<KeyModifiers>(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
		return lhs;
	}

	[[nodiscard]]
	constexpr KeyModifiers& operator^=(KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		lhs = static_cast<KeyModifiers>(static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs));
		return lhs;
	}
}
