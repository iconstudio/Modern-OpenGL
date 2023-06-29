module;
#include "Internal.hpp"

export module Glib.Device.Event:Definitions;
import <compare>;

namespace gl::device
{
	export using RawDeviceCommand = ::tagMSG;
	export using DeviceCommandIDType = decltype(RawDeviceCommand::message);

	export enum class [[nodiscard]] EventID : DeviceCommandIDType
	{
		None = 0,
		Create = WM_CREATE,
		Destroy = WM_DESTROY,

		Move = WM_MOVE,
		Size = WM_SIZE,
		Activate = WM_ACTIVATE,
		SetKeyboardFocus = WM_SETFOCUS,
		KillKeyboardFocus = WM_KILLFOCUS,
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
		SysCommand = WM_SYSCOMMAND,

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

	struct [[nodiscard]] EventIDWrapper
	{
		constexpr EventIDWrapper() noexcept = default;
		constexpr ~EventIDWrapper() noexcept = default;

		explicit constexpr EventIDWrapper(const EventID& event_id) noexcept
			: id(event_id)
		{}

		explicit constexpr EventIDWrapper(EventID&& event_id) noexcept
			: id(static_cast<EventID&&>(event_id))
		{}

		[[nodiscard]]
		constexpr bool operator==(const EventID& event_id) const noexcept
		{
			return id == event_id;
		}

		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const EventID& event_id) const noexcept
		{
			return static_cast<DeviceCommandIDType>(id) <=> static_cast<DeviceCommandIDType>(event_id);
		}

		constexpr operator EventID& () & noexcept
		{
			return id;
		}

		constexpr operator const EventID& () const& noexcept
		{
			return id;
		}

		constexpr operator EventID && () && noexcept
		{
			return static_cast<EventID&&>(id);
		}

		constexpr operator const EventID && () const&& noexcept
		{
			return static_cast<const EventID&&>(id);
		}

		constexpr EventIDWrapper(const EventIDWrapper&) noexcept = default;
		constexpr EventIDWrapper(EventIDWrapper&&) noexcept = default;
		constexpr EventIDWrapper& operator=(const EventIDWrapper&) noexcept = default;
		constexpr EventIDWrapper& operator=(EventIDWrapper&&) noexcept = default;
		constexpr bool operator==(const EventIDWrapper&) const noexcept = default;
		constexpr std::strong_ordering operator<=>(const EventIDWrapper&) const noexcept = default;

		EventIDWrapper& operator=(EventID) = delete;

		EventID id;
	};

	export struct [[nodiscard]] KeyboardEventID : public EventIDWrapper
	{
		static constexpr EventID GUARD_FIRST = EventID{ WM_KEYFIRST };
		static constexpr EventID GUARD_LAST = EventID{ WM_KEYLAST };

		static constexpr EventID Pressed = EventID{ WM_KEYDOWN };
		static constexpr EventID Released = EventID{ WM_KEYUP };
		static constexpr EventID CharPressed = EventID{ WM_CHAR };
		static constexpr EventID CharReleased = EventID{ WM_DEADCHAR };

		static constexpr EventID AltPressed = EventID{ WM_SYSKEYDOWN };
		static constexpr EventID AltReleased = EventID{ WM_SYSKEYUP };
		static constexpr EventID AltCharPressed = EventID{ WM_SYSCHAR };
		static constexpr EventID AltCharReleased = EventID{ WM_SYSDEADCHAR };

		constexpr KeyboardEventID(const KeyboardEventID&) noexcept = default;
		constexpr KeyboardEventID(KeyboardEventID&&) noexcept = default;
		constexpr KeyboardEventID& operator=(const KeyboardEventID&) noexcept = default;
		constexpr KeyboardEventID& operator=(KeyboardEventID&&) noexcept = default;
		KeyboardEventID& operator=(EventID) = delete;
	};

	export struct [[nodiscard]] MouseEventID : public EventIDWrapper
	{
		static constexpr EventID GUARD_FIRST = EventID{ WM_MOUSEFIRST };
		static constexpr EventID GUARD_LAST = EventID{ WM_MOUSELAST };

		static constexpr EventID Moved = EventID{ WM_MOUSEMOVE };
		static constexpr EventID Covered = EventID{ WM_MOUSEHOVER };
		static constexpr EventID Uncovered = EventID{ WM_MOUSELEAVE };

		static constexpr EventID VtWheel = EventID{ WM_MOUSEWHEEL };
		static constexpr EventID HvWheel = EventID{ WM_MOUSEHWHEEL };

		static constexpr EventID LtPressed = EventID{ WM_LBUTTONDOWN };
		static constexpr EventID LtReleased = EventID{ WM_LBUTTONUP };
		static constexpr EventID LtDoubleClicked = EventID{ WM_LBUTTONDBLCLK };

		static constexpr EventID RtPressed = EventID{ WM_RBUTTONDOWN };
		static constexpr EventID RtReleased = EventID{ WM_RBUTTONUP };
		static constexpr EventID RtDoubleClicked = EventID{ WM_RBUTTONDBLCLK };

		static constexpr EventID MdPressed = EventID{ WM_MBUTTONDOWN };
		static constexpr EventID MdReleased = EventID{ WM_MBUTTONUP };
		static constexpr EventID MdDoubleClicked = EventID{ WM_MBUTTONDBLCLK };

		constexpr MouseEventID(const MouseEventID&) noexcept = default;
		constexpr MouseEventID(MouseEventID&&) noexcept = default;
		constexpr MouseEventID& operator=(const MouseEventID&) noexcept = default;
		constexpr MouseEventID& operator=(MouseEventID&&) noexcept = default;
		MouseEventID& operator=(EventID) = delete;
	};
}
