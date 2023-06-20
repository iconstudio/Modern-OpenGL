module;
#include "Internal.hpp"
export module Glib.Device.Window:Option;

export namespace gl::device
{
	enum class WindowOption : unsigned long
	{
		Modal = 0x00000001L,
		NoParentNotify = 0x00000004L,
		TopMost = 0x00000008L,
		AcceptFiles = 0x00000010L,
		Transparent = 0x00000020L,
		MDIChild = 0x00000040L,
		ToolWindow = 0x00000080L,
		WindowEdge = 0x00000100L,
		ClientEdge = 0x00000200L,
		ContextHelp = 0x00000400L,

		Right = 0x00001000L,
		Left = 0x00000000L,
		RTLReading = 0x00002000L,
		LTRReading = 0x00000000L,
		LeftScrollBar = 0x00004000L,
		RightScrollBar = 0x00000000L,

		ControlParent = 0x00010000L,
		StaticEdge = 0x00020000L,
		AppWindow = 0x00040000L
	};

	namespace options
	{
		inline constexpr WindowOption Default = WindowOption{ WS_EX_OVERLAPPEDWINDOW };
		inline constexpr WindowOption Palette = WindowOption{ WS_EX_PALETTEWINDOW };
	}

	[[nodiscard]]
	constexpr unsigned long Export(const WindowOption& option) noexcept
	{
		return static_cast<unsigned long>(option);
	}

	[[nodiscard]]
	constexpr unsigned long Export(WindowOption&& option) noexcept
	{
		return static_cast<unsigned long>(option);
	}

	[[nodiscard]]
	constexpr WindowOption operator|(const WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		return static_cast<WindowOption>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr WindowOption operator&(const WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		return static_cast<WindowOption>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr WindowOption operator^(const WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		return static_cast<WindowOption>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
	}

	[[nodiscard]]
	constexpr WindowOption operator~(const WindowOption& lhs) noexcept
	{
		return static_cast<WindowOption>(~static_cast<int>(lhs));
	}

	constexpr WindowOption& operator|=(WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		lhs = static_cast<WindowOption>(static_cast<int>(lhs) | static_cast<int>(rhs));
		return lhs;
	}

	constexpr WindowOption& operator&=(WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		lhs = static_cast<WindowOption>(static_cast<int>(lhs) & static_cast<int>(rhs));
		return lhs;
	}

	constexpr WindowOption& operator^=(WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		lhs = static_cast<WindowOption>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
		return lhs;
	}

	[[nodiscard]]
	constexpr bool has(const WindowOption& lhs, const WindowOption& rhs) noexcept
	{
		return (static_cast<int>(lhs) & static_cast<int>(rhs)) != 0;
	}
}
