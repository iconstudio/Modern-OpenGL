export module Glib:ClearBits;

export namespace gl
{
	enum class [[nodiscard]] Clearance : unsigned int
	{
		Color = 0x00004000,
		Depth = 0x00000100,
		Stencil = 0x00000400,
		DepthStencil = 0x00004004,
		Accum = 0x00000200,
	};
}
