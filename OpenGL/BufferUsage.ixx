export module Glib:BufferUsage;
import <cstdint>;

export namespace gl::buffer
{
	enum class [[nodiscard]] BufferType : std::uint32_t
	{
		None = 0,
		Vertex = 0x8892,
		Array = Vertex,
		Index = 0x8893,
		ElementArray = Index,
		Uniform = 0x8A11,
		PixelPack = 0x88EB,
		PixelUnpack = 0x88EC,
		Texture = 0x8C2A,
		TransformFeedback = 0x8C8E,
		CopyRead = 0x8F36,
		CopyWrite = 0x8F37,
		DrawIndirect = 0x8F3F,

		AtomicCounter = 0x92C0,
		ShaderStorage = 0x90D2,
		DispatchIndirect = 0x90EE,
		Query = 0x9192
	};
}
