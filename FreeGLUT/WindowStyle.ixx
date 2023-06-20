module;
#include "Internal.hpp"
export module Glib.Device.Window:Style;

export namespace gl::device
{
	enum class WindowStyle : unsigned int
	{
		Default = WS_OVERLAPPED,
		Visible = WS_VISIBLE,
		Disabled = WS_DISABLED,

		Frame = WS_BORDER,
		Caption = WS_DLGFRAME,
		ThickFrame = WS_THICKFRAME,
		Dialogue = WS_CAPTION,

		Maximize = WS_MAXIMIZE,
		MaximizeBox = WS_MAXIMIZEBOX,
		Minimize = WS_MINIMIZE,
		Iconic = Minimize, // WS_ICONIC == WS_MINIMIZE
		MinimizeBox = WS_MINIMIZEBOX,
		Popup = WS_POPUP,
		HorizontalScroll = WS_HSCROLL,
		VerticalScroll = WS_VSCROLL,

		Child = WS_CHILD,
		ClipChildren = WS_CLIPCHILDREN,
		ClipSiblings = WS_CLIPSIBLINGS,
		Group = WS_GROUP,
	};

	[[nodiscard]]
	constexpr WindowStyle operator|(const WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		return static_cast<WindowStyle>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr WindowStyle operator&(const WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		return static_cast<WindowStyle>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr WindowStyle operator^(const WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		return static_cast<WindowStyle>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr WindowStyle operator~(const WindowStyle& lhs) noexcept
	{
		return static_cast<WindowStyle>(~static_cast<int>(lhs));
	}

	constexpr WindowStyle& operator|=(WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		lhs = static_cast<WindowStyle>(static_cast<int>(lhs) | static_cast<int>(rhs));
		return lhs;
	}

	constexpr WindowStyle& operator&=(WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		lhs = static_cast<WindowStyle>(static_cast<int>(lhs) & static_cast<int>(rhs));
		return lhs;
	}

	constexpr WindowStyle& operator^=(WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		lhs = static_cast<WindowStyle>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
		return lhs;
	}

	[[nodiscard]]
	constexpr bool has(const WindowStyle& lhs, const WindowStyle& rhs) noexcept
	{
		return (static_cast<int>(lhs) & static_cast<int>(rhs)) != 0;
	}
}
