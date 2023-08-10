export module Glib:BufferType;
import <cstdint>;

export namespace gl::buffer
{
	enum class [[nodiscard]] BufferUsage : std::uint32_t
	{
		None = 0,
		StaticDraw = 0x88E4,
		StaticRead = 0x88E5,
		StaticCopy = 0x88E6,
		DynamicDraw = 0x88E8,
		DynamicRead = 0x88E9,
		DynamicCopy = 0x88EA,
		StreamDraw = 0x88E0,
		StreamRead = 0x88E1,
		StreamCopy = 0x88E2
	};
}
