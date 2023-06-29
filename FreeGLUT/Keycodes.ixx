module;
//#include "Internal.hpp"
export module Glib.Device.IO.Keyboard:KeyCodes;

export namespace gl::device::io
{
	enum class [[nodiscard]] KeyCode : int
	{
		Shift = 0x10, Control = 0x11, Alt = 0x12,
		BackSpace = 0x0008, Tab = 0x0009,
		Enter = 0x000D, Escape = 0x001B,
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

		PageUp = 0x21, PageDown = 0x22,
		End = 0x23, Home = 0x24,
		Left = 0x25, Up = 0x26, Right = 0x27, Down = 0x28,
		Snapshot = 0x2C, PrintScreen = 0x2C,
		Insert = 0x2D, Delete = 0x2E,

		F1 = 0x70, F2 = 0x71, F3 = 0x72,
		F4 = 0x73, F5 = 0x74, F6 = 0x75,
		F7 = 0x76, F8 = 0x77, F9 = 0x78,
		F10 = 0x79, F11 = 0x7A, F12 = 0x7B,
		F13 = 0x7C, F14 = 0x7D, F15 = 0x7E,
		F16 = 0x7F, F17 = 0x80, F18 = 0x81,
		F19 = 0x82, F20 = 0x83, F21 = 0x84,
		F22 = 0x85, F23 = 0x86, F24 = 0x87,

#ifdef _WIN32
		System = 0x5B,
#endif
	};
}
