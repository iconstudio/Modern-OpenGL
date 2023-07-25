export module Glib:Transform;
import :TransformState;

export namespace gl
{
	namespace transform
	{
		void LoadIdentity() noexcept;

		void GetCurrentMatrix(TransformMode state, float(&matrix)[16]) noexcept;
		void GetCurrentMatrix(TransformMode state, float* const& matrix) noexcept;
		void GetCurrentMatrix(TransformMode state, double(&matrix)[16]) noexcept;
		void GetCurrentMatrix(TransformMode state, double* const& matrix) noexcept;
	}
}
