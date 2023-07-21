export module Glib:TransformState;

export namespace gl
{
	enum class [[nodiscard]] TransformMode : unsigned int
	{
		ModelView = 0x1700,
		Projection = 0x1701,
		Texture = 0x1702,
	};
}
