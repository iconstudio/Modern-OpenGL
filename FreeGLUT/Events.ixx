module;
#include "Internal.hpp"
export module Glib.Device.Event:Definitions;

export namespace gl::device
{
	using RawDeviceCommand = ::tagMSG;
	using DeviceCommandIDType = decltype(RawDeviceCommand::message);

	enum class [[nodiscard]] EventID : DeviceCommandIDType
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

	enum class [[nodiscard]] KeyboardEvent : DeviceCommandIDType
	{
		GUARD_FIRST = WM_KEYFIRST,
		GUARD_LAST = WM_KEYLAST,

		Pressed = WM_KEYDOWN,
		Released = WM_KEYUP,
		CharPressed = WM_CHAR,
		CharReleased = WM_DEADCHAR,

		AltPressed = WM_SYSKEYDOWN,
		AltReleased = WM_SYSKEYUP,
		AltCharPressed = WM_SYSCHAR,
		AltCharReleased = WM_SYSDEADCHAR,
	};

	enum class [[nodiscard]] MouseEvent : DeviceCommandIDType
	{
		GUARD_FIRST = WM_MOUSEFIRST,
		GUARD_LAST = WM_MOUSELAST,

		Moved = WM_MOUSEMOVE,
		Covered = WM_MOUSEHOVER,
		Uncovered = WM_MOUSELEAVE,

		VtWheel = WM_MOUSEWHEEL,
		HvWheel = WM_MOUSEHWHEEL,

		LtPressed = WM_LBUTTONDOWN,
		LtReleased = WM_LBUTTONUP,
		LtDoubleClicked = WM_LBUTTONDBLCLK,

		RtPressed = WM_RBUTTONDOWN,
		RtReleased = WM_RBUTTONUP,
		RtDoubleClicked = WM_RBUTTONDBLCLK,

		MdPressed = WM_MBUTTONDOWN,
		MdReleased = WM_MBUTTONUP,
		MdDoubleClicked = WM_MBUTTONDBLCLK,
	};
}
