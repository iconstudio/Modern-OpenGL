module;
#include <windows.system.h>
export module Glib.Device.IO.Keyboard:KeyCodes;

using enum ABI::Windows::System::VirtualKey;

export namespace gl::device::io
{
	enum class [[nodiscard]] KeyCode : int
	{
		Shift = VirtualKey_Shift,
		Control = VirtualKey_Control,
		Alt = VirtualKey_Menu,

		BackSpace = VirtualKey_Back,
		Tab = VirtualKey_Tab,
		Enter = VirtualKey_Enter,
		Escape = VirtualKey_Escape,
		Pause = VirtualKey_Pause,
		CapitalLock = VirtualKey_CapitalLock,
		System = VirtualKey_LeftWindows,
		System2 = VirtualKey_RightWindows,

		Space = ' ',
		Exclamation = '!', DoubleQuote = '"', Hash = '#', Dollar = '$',
		Percent = '%', Ampersand = '&', Quote = '\'',
		LParen = '(', RParen = ')',
		Asterisk = '*', Plus = '+', Comma = ',', Minus = '-', Period = '.', Slash = '/',
		Zero = '0', One = '1', Two = '2', Three = '3', Four = '4',
		Five = '5', Six = '6', Seven = '7', Eight = '8', Nine = '9',
		Colon = ':', Semicolon = ';',
		LessThan = '<', Equal = '=', GreaterThan = '>',
		Question = '?', At = '@',

		A = 'A', B = 'B', C = 'C',
		D = 'D', E = 'E', F = 'F',
		G = 'G', H = 'H', I = 'I',
		J = 'J', K = 'K', L = 'L',
		M = 'M', N = 'N', O = 'O',
		P = 'P', Q = 'Q', R = 'R',
		S = 'S', T = 'T', U = 'U',
		V = 'V', W = 'W', X = 'X',
		Y = 'Y', Z = 'Z',
		LBracket = '[', Backslash = '\\', RBracket = ']',
		Caret = '^', Underscore = '_', GraveAccent = '`',

		a = 'a', b = 'b', c = 'c',
		d = 'd', e = 'e', f = 'f',
		g = 'g', h = 'h', i = 'i',
		j = 'j', k = 'k', l = 'l',
		m = 'm', n = 'n', o = 'o',
		p = 'p', q = 'q', r = 'r',
		s = 's', t = 't', u = 'u',
		v = 'v', w = 'w', x = 'x',
		y = 'y', z = 'z',
		LBrace = '{', Pipe = '|', RBrace = '}', Tilde = '~',

		PageUp = VirtualKey_PageUp, PageDown = VirtualKey_PageDown,
		End = VirtualKey_End, Home = VirtualKey_Home,
		Left = VirtualKey_Left, Up = VirtualKey_Up, Right = VirtualKey_Right, Down = VirtualKey_Down,
		Snapshot = VirtualKey_Snapshot, PrintScreen = VirtualKey_Snapshot,
		Insert = VirtualKey_Insert, Delete = VirtualKey_Delete,

		F1 = VirtualKey_F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
	};
}
