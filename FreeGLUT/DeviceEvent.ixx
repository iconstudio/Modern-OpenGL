module;
#include "Internal.hpp"

export module Glib.Device.Event;
import <compare>;
import Utility;

export namespace gl::device
{
	using RawDeviceCommand = ::tagMSG;
	using DeviceCommandIDType = decltype(RawDeviceCommand::message);

	enum class [[nodiscard]] PeekCmd : unsigned int
	{
		DontRemove = PM_NOREMOVE,
		Remove = PM_REMOVE,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
	};

	enum class [[nodiscard]] EventID : DeviceCommandIDType
	{
		None = 0,
		Create = WM_CREATE,
		Destroy = WM_DESTROY,

		Move = WM_MOVE,
		Size = WM_SIZE,
		Activate = WM_ACTIVATE,
		SetFocus = WM_SETFOCUS,
		KillFocus = WM_KILLFOCUS,
		Enable = WM_ENABLE,
		SetRedraw = WM_SETREDRAW,
		SetText = WM_SETTEXT,
		GetText = WM_GETTEXT,
		GetTextLength = WM_GETTEXTLENGTH,
		Paint = WM_PAINT,

		Close = WM_CLOSE,
		QueryEndSession = WM_QUERYENDSESSION,
		Quit = WM_QUIT,
		CleanupMemory = WM_NCDESTROY,

		KeyDown = WM_KEYDOWN,
		KeyUp = WM_KEYUP,
		Char = WM_CHAR,
		DeadChar = WM_DEADCHAR,

		SysKeyDown = WM_SYSKEYDOWN,
		SysKeyUp = WM_SYSKEYUP,
		SysChar = WM_SYSCHAR,
		SysDeadChar = WM_SYSDEADCHAR,

		MouseMove = WM_MOUSEMOVE,
		MouseHover = WM_MOUSEHOVER,
		MouseLeave = WM_MOUSELEAVE,
		MouseWheel = WM_MOUSEWHEEL,
		MouseHWheel = WM_MOUSEHWHEEL,
		LButtonDown = WM_LBUTTONDOWN,
		LButtonUp = WM_LBUTTONUP,
		LButtonDoubleClick = WM_LBUTTONDBLCLK,
		RButtonDown = WM_RBUTTONDOWN,
		RButtonUp = WM_RBUTTONUP,
		RButtonDoubleClick = WM_RBUTTONDBLCLK,
		MButtonDown = WM_MBUTTONDOWN,
		MButtonUp = WM_MBUTTONUP,
		MButtonDoubleClick = WM_MBUTTONDBLCLK,

		ChangedCapture = WM_CAPTURECHANGED,
	};

	/// <summary>
	/// WPARAM from EventID::Activate
	/// </summary>
	enum class [[nodiscard]] DeviceActivation : unsigned short
	{
		Activated = WA_ACTIVE,
		ClickActive = WA_CLICKACTIVE,
		Inactivated = WA_INACTIVE,
	};

	[[nodiscard]]
	constexpr bool operator==(const DeviceActivation& state, const unsigned short& rhs) noexcept
	{
		return static_cast<unsigned short>(state) == rhs;
	}

#ifdef Event
#undef Event
#endif
	struct [[nodiscard]] Event final
	{
		constexpr Event() noexcept = default;
		constexpr ~Event() noexcept = default;

		constexpr Event(const RawDeviceCommand& msg) noexcept
			: id(EventID{ msg.message })
			, wParam(msg.wParam), lParam(msg.lParam)
			, time(msg.time)
		{}

		constexpr Event(RawDeviceCommand&& msg) noexcept
			: id(EventID{ util::move(msg.message) })
			, wParam(util::move(msg.wParam)), lParam(util::move(msg.lParam))
			, time(util::move(msg.time))
		{}

		constexpr Event(const EventID& msg, const unsigned long long& lhs, const long long& rhs, const unsigned long& tick) noexcept
			: id(msg), wParam(lhs), lParam(rhs)
			, time(tick)
		{}

		[[nodiscard]]
		constexpr bool operator==(const Event& rhs) const noexcept
		{
			return id == rhs.id && wParam == rhs.wParam && lParam == rhs.lParam;
		}

		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const Event& rhs) const noexcept
		{
			auto comp_id = id <=> rhs.id;
			if (comp_id != std::strong_ordering::equal)
			{
				return comp_id;
			}

			auto comp_wp = wParam <=> rhs.wParam;
			if (comp_wp != std::strong_ordering::equal)
			{
				return comp_wp;
			}

			auto comp_lp = lParam <=> rhs.wParam;
			if (comp_lp != std::strong_ordering::equal)
			{
				return comp_lp;
			}

			return time <=> rhs.time;
		}

		constexpr Event(const Event&) noexcept = default;
		constexpr Event(Event&&) noexcept = default;
		constexpr Event& operator=(const Event&) noexcept = default;
		constexpr Event& operator=(Event&&) noexcept = default;

		EventID id = EventID::None;
		unsigned long long wParam = 0;
		long long lParam = 0;
		unsigned long time = 0;
	};
}
