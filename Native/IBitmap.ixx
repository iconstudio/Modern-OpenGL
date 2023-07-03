module;
#include "Internal.hpp"

export module Glib.Device.Resource.IBitmap;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device::resource
{
	class [[nodiscard]] ImageFactory
	{
	public:
	};

	class [[nodiscard]] Image : public IHandle<native::RawBitmap>
	{
	public:
		[[nodiscard]] Image Copy() const noexcept;
		[[nodiscard]] bool TryCopy(Image& output) const noexcept;

		bool Destroy() noexcept;

		void Mirror() noexcept;
		void Flip() noexcept;

		void Rotate(float angle) noexcept;
		void RotateR(float angle) noexcept;
		void RotateL(float angle) noexcept;

		bool Fill() noexcept;

		bool Draw(const native::NativeSurface& hdc, const int& x, const int& y) const noexcept;

		bool GetPixel(const int& x, const int& y, int& output) const noexcept;
		int GetWidth() const noexcept;
		int GetHeight() const noexcept;
	};
}
