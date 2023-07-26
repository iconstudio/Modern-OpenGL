export module Glib:Primitive;
import <cstdint>;

export namespace gl
{
	enum class [[nodiscard]] Primitive : std::uint32_t
	{
		Points = 0x0000U,
		Lines = 0x0001U,
		LineLoop = 0x0002U,
		LineStrip = 0x0003U,
		Triangles = 0x0004U,
		TriangleStrip = 0x0005U,
		TriangleFan = 0x0006U,
		Quads = 0x0007U,
		QuadStrip = 0x0008U,
		Polygon = 0x0009U,
	};
}
