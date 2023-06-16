export module Glut.Keycodes;

export namespace gl
{
	enum class [[nodiscard]] Keycodes : int
	{
		BACKSPACE = 0x0008, TAB = 0x0009,
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

		F1 = 0x0001, F2 = 0x0002, F3 = 0x0003,
		F4 = 0x0004, F5 = 0x0005, F6 = 0x0006,
		F7 = 0x0007, F8 = 0x0008, F9 = 0x0009,
		F10 = 0x000A, F11 = 0x000B, F12 = 0x000C,
		LEFT = 0x0064, UP = 0x0065, RIGHT = 0x0066, DOWN = 0x0067,
		PAGE_UP = 0x0068, PAGE_DOWN = 0x0069,
		HOME = 0x006A, END = 0x006B,
		INSERT = 0x006C,
	};
}
