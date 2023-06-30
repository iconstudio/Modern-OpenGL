module;
#include "Internal.hpp"

export module Glib.Device.Event:ID;
import <compare>;

export namespace gl::device
{
	using RawEvent = ::tagMSG;
	using DeviceCommandIDType = decltype(RawEvent::message);

	enum class [[nodiscard]] EventID : DeviceCommandIDType
	{
		None = 0,
		Create = WM_CREATE,
		Destroy = WM_DESTROY,
		Show = WM_SHOWWINDOW,

		NCActivate = WM_NCACTIVATE,
		NCCreate = WM_NCCREATE,
		NCDestroy = WM_NCDESTROY,
		NCMouseMove = WM_NCMOUSEMOVE,

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
		ChangedSetting = WM_SETTINGCHANGE,
		ChangedDPI = WM_DPICHANGED,
		ChangedTheme = WM_THEMECHANGED,
		ChangedStaticColor = WM_SYSCOLORCHANGE, // GetSysColor, SetSysColor, GetSysColorBrush, SetSysColorBrush
		ChangedUserColor = WM_DWMCOLORIZATIONCOLORCHANGED, // DwmGetColorizationColor, DwmSetColorizationColor

		Close = WM_CLOSE,
		QueryEndSession = WM_QUERYENDSESSION,
		Quit = WM_QUIT,
		CleanupMemory = WM_NCDESTROY,

		KeyboardFirst = WM_KEYFIRST,
		KeyDown = WM_KEYDOWN,
		KeyUp = WM_KEYUP,
		Char = WM_CHAR,
		DeadChar = WM_DEADCHAR,

		SysKeyDown = WM_SYSKEYDOWN,
		SysKeyUp = WM_SYSKEYUP,
		SysChar = WM_SYSCHAR,
		SysDeadChar = WM_SYSDEADCHAR,
		SysCommand = WM_SYSCOMMAND,
		KeyboardLast = WM_KEYLAST,

		MouseFirst = WM_MOUSEFIRST,
		MouseMove = WM_MOUSEMOVE,
		LButtonDown = WM_LBUTTONDOWN,
		LButtonUp = WM_LBUTTONUP,
		LButtonDoubleClick = WM_LBUTTONDBLCLK,
		RButtonDown = WM_RBUTTONDOWN,
		RButtonUp = WM_RBUTTONUP,
		RButtonDoubleClick = WM_RBUTTONDBLCLK,
		MButtonDown = WM_MBUTTONDOWN,
		MButtonUp = WM_MBUTTONUP,
		MButtonDoubleClick = WM_MBUTTONDBLCLK,
		MouseWheel = WM_MOUSEWHEEL,
		MouseHWheel = WM_MOUSEHWHEEL,
		MouseHover = WM_MOUSEHOVER,
		MouseLeave = WM_MOUSELEAVE,
		MouseLast = WM_MOUSELAST,

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
		inline friend constexpr
			bool
			operator==(const EventIDWrapper& self, const EventID& event_id) noexcept
		{
			return self.id == event_id;
		}

		[[nodiscard]]
		inline friend constexpr
			std::strong_ordering
			operator<=>(const EventIDWrapper& self, const EventID& event_id) noexcept
		{
			return static_cast<DeviceCommandIDType>(self.id) <=> static_cast<DeviceCommandIDType>(event_id);
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

		EventID id = EventID::None;
	};

	struct [[nodiscard]] KeyboardEventID : public EventIDWrapper
	{
		KeyboardEventID& operator=(EventID) = delete;

	private:
		KeyboardEventID() noexcept = default;

		using EventIDWrapper::EventIDWrapper;
	};

	struct [[nodiscard]] MouseEventID : public EventIDWrapper
	{
		MouseEventID& operator=(EventID) = delete;

	private:
		MouseEventID() noexcept = default;

		using EventIDWrapper::EventIDWrapper;
	};
}
