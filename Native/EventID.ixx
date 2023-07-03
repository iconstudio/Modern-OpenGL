module;
#include "Internal.hpp"

export module Glib.Device.Event:ID;
export import :Implement;

export namespace gl::device
{
	using RawEvent = ::tagMSG;
	using RawEventID = decltype(RawEvent::message);

	enum class [[nodiscard]] EventID : RawEventID
	{
		None = 0,
		Create = WM_CREATE,
		Destroy = WM_DESTROY,
		Show = WM_SHOWWINDOW,

		Initiate = WM_NCCREATE, // Create window handle and set the window data
		Annihilate = WM_NCDESTROY, // Cleanup memory
		TestMouse = WM_NCHITTEST, // Should use the result of DefWindowProc to handle this message
		NCActivate = WM_NCACTIVATE,
		GetTestMouse = WM_NCMOUSEMOVE, // Get the mouse position in the non-client area

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

		/// <summary>
		/// PaintFrame -> EraseBackground -> Paint
		/// </summary>
		Paint = WM_PAINT, // (3) BeginPaint, EndPaint
		EraseBackground = WM_ERASEBKGND, // (2) WNDCLASS.hbrBackground
		PaintFrame = WM_NCPAINT, // (1) wparam is HRGN. Use it with GetDCEx

		Close = WM_CLOSE,
		QueryEndSession = WM_QUERYENDSESSION,
		Quit = WM_QUIT,

		ShowCursor = WM_SETCURSOR,
		WindowPositionChanging = WM_WINDOWPOSCHANGING,
		WindowPositionChanged = WM_WINDOWPOSCHANGED,
		WindowStyleChanged = WM_STYLECHANGED,

		ChangedSetting = WM_SETTINGCHANGE,
		ChangedDPI = WM_DPICHANGED,
		ChangedTheme = WM_THEMECHANGED,
		ChangedStaticColor = WM_SYSCOLORCHANGE, // GetSysColor, SetSysColor, GetSysColorBrush, SetSysColorBrush
		ChangedUserColor = WM_DWMCOLORIZATIONCOLORCHANGED, // DwmGetColorizationColor, DwmSetColorizationColor

		KeyboardFirst = WM_KEYFIRST, // 256
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

		MouseFirst = WM_MOUSEFIRST, // 512
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
