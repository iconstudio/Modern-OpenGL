export module Glib.Device.IO.Keyboard:Modifier;

export namespace gl::device::io
{
	/// <summary>
	/// glutGetModifiers
	/// </summary>
	enum class [[nodiscard]] KeyModifiers : int
	{
		Shift = 0x0001,
		Ctrl = 0x0002,
		Alt = 0x0004
	};

	inline constexpr KeyModifiers Shift = KeyModifiers::Shift;
	inline constexpr KeyModifiers Ctrl = KeyModifiers::Ctrl;
	inline constexpr KeyModifiers Alt = KeyModifiers::Alt;

	[[nodiscard]]
	constexpr KeyModifiers operator|(const KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		return static_cast<KeyModifiers>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers operator&(const KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		return static_cast<KeyModifiers>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers operator^(const KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		return static_cast<KeyModifiers>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers operator~(const KeyModifiers& lhs) noexcept
	{
		return static_cast<KeyModifiers>(~static_cast<int>(lhs));
	}

	[[nodiscard]]
	constexpr KeyModifiers& operator|=(KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		lhs = static_cast<KeyModifiers>(static_cast<int>(lhs) | static_cast<int>(rhs));
		return lhs;
	}

	[[nodiscard]]
	constexpr KeyModifiers& operator&=(KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		lhs = static_cast<KeyModifiers>(static_cast<int>(lhs) & static_cast<int>(rhs));
		return lhs;
	}

	[[nodiscard]]
	constexpr KeyModifiers& operator^=(KeyModifiers& lhs, const KeyModifiers& rhs) noexcept
	{
		lhs = static_cast<KeyModifiers>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
		return lhs;
	}
}
