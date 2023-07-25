export module Glib:Transform;
import :TransformState;

export namespace gl
{
	namespace transform
	{
		void LoadIdentity() noexcept;
		void LookAt(float x, float y, float z, float tx, float ty, float tz, float ux, float uy, float uz) noexcept;
		void LookAt(double x, double y, double z, double tx, double ty, double tz, double ux, double uy, double uz) noexcept;
		void Projection(float fov, float aspect, float near, float far) noexcept;
		void Projection(double fov, double aspect, double near, double far) noexcept;
		void Ortho(float left, float right, float bottom, float top, float near, float far) noexcept;
		void Ortho(double left, double right, double bottom, double top, double near, double far) noexcept;

		void Translate(float x, float y, float z) noexcept;
		void Translate(double x, double y, double z) noexcept;
		void Rotate(float angle, float x, float y, float z) noexcept;
		void Rotate(double angle, double x, double y, double z) noexcept;
		void Scale(float x, float y, float z) noexcept;
		void Scale(double x, double y, double z) noexcept;

		void GetCurrentMatrix(TransformMode state, float(&matrix)[16]) noexcept;
		void GetCurrentMatrix(TransformMode state, float* const& matrix) noexcept;
		void GetCurrentMatrix(TransformMode state, double(&matrix)[16]) noexcept;
		void GetCurrentMatrix(TransformMode state, double* const& matrix) noexcept;
	}
}
