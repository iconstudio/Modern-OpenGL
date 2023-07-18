export module Glib.Culling;
import :Face;

export namespace gl
{
	void Culling(Face face) noexcept;
	void CullingDirection(bool clockwise) noexcept;
}
