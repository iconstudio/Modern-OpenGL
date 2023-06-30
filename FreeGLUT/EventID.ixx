module;
#include "Internal.hpp"

export module Glib.Device.Event:ID;
export import :Implement;

export namespace gl::device
{
	enum class [[nodiscard]] EventID : RawEventID
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
}
