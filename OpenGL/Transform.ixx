export module Glib:Transform;
import :TransformState;

export namespace gl
{
	namespace transform
	{
		void LoadIdentity() noexcept;
		void GetMatrix(TransformMode mode, float* matrix) noexcept;
	}
}
