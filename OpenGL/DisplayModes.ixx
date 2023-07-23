export module Glib:DisplayModes;
import <cstdint>;

export namespace gl
{
	enum class [[nodiscard]] DisplayModes : std::uint32_t
	{
		RGB = 0x0000U, RGBA = 0x0000U,
		INDEX = 0x0001U, SINGLE = 0x0000U, DOUBLE = 0x0002U, ACCUM = 0x0004U,
		ALPHA = 0x0008U,
		DEPTH = 0x0010U, STENCIL = 0x0020U, MULTISAMPLE = 0x0080U, STEREO = 0x0100U,
		LUMINANCE = 0x0200U,
	};
}