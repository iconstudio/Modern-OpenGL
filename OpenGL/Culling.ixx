export module Glib.Culling;
import :Face;

export namespace gl
{
	enum class [[nodiscard]] CullFace : unsigned int
	{
		Front = static_cast<unsigned int>(Face::Front),
		Back = static_cast<unsigned int>(Face::Back),
		FrontAndBack = static_cast<unsigned int>(Face::FrontAndBack),
	};
}
