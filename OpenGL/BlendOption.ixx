export module Glib.Blender:Option;

export namespace gl
{
	enum class [[nodiscard]] BlendOption : unsigned int
	{
		Invalid = static_cast<unsigned int>(-1),
		Zero = 0x0000,
		One = 0x0001,
		SourceColour = 0x0300,
		InvertedSrcColour = 0x0301,
		SourceAlpha = 0x0302,
		InvertedSrcAlpha = 0x0303,
		DestColour = 0x0306,
		InvertedDstColour = 0x0307,
		DestAlpha = 0x0304,
		InvertedDstAlpha = 0x0305,
		SaturateSourceAlpha = 0x0308
	};
}
