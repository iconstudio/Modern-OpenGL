export module Glib:Face;

export namespace gl
{
	enum class [[nodiscard]] Face : unsigned int
	{
		Front = 0x0404,
		Back = 0x0405,
		FrontAndBack = 0x0408,
		LEFT = 0x0406,
		RIGHT = 0x0407,
	};
}
