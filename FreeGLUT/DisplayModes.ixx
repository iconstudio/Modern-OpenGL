export module Glut.Display:Modes;

export namespace gl::display
{
	enum class [[nodiscard]] DisplayModes : int
	{
		RGB = 0x0000, RGBA = 0x0000,
		INDEX = 0x0001, SINGLE = 0x0000, DOUBLE = 0x0002, ACCUM = 0x0004,
		ALPHA = 0x0008,
		DEPTH = 0x0010, STENCIL = 0x0020, MULTISAMPLE = 0x0080, STEREO = 0x0100,
		LUMINANCE = 0x0200,
	};
}