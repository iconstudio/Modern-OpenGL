export module Glib.Culling:Face;
import <cstdint>;

export namespace gl
{
	enum class [[nodiscard]] Face : std::uint32_t
	{
		Front = 0x0404U,
		Back = 0x0405U,
		FrontAndBack = 0x0408U,
	};
}
