module;
#include "Internal.hpp"

export module Glib.Device.Resource.IBitmap;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IGraphics;
import Glib.Device.ISurface;
import Glib.Device.Colour;

export namespace gl::device::resource
{
	class [[nodiscard]] ImageFactory
	{
	public:
	};

	/// <summary>
	/// Bitmap Viewer
	/// </summary>
	class [[nodiscard]] IBitmap : public IGraphics<IBitmap, native::RawBitmap>
	{
	public:
		using base = IGraphics<IBitmap, native::RawBitmap>;

		constexpr IBitmap() noexcept = default;
		explicit IBitmap(const handle_type& handle) noexcept;
		explicit IBitmap(handle_type&& handle) noexcept;
		~IBitmap() noexcept;

		constexpr IBitmap(nullptr_t) noexcept
			: base(nullifier)
		{}

		[[nodiscard]] IBitmap Copy() const noexcept;
		[[nodiscard]] bool TryCopy(IBitmap& output) const noexcept;

		bool Destroy() noexcept;

		void Mirror() noexcept;
		void Flip() noexcept;

		void Rotate(float angle) noexcept;
		void RotateR(float angle) noexcept;
		void RotateL(float angle) noexcept;

		bool Fill() noexcept;

		bool Draw(const ISurface& context, const int& x, const int& y) const noexcept;

		bool GetPixel(const ISurface& context, const int& x, const int& y, Colour& output) const;
		int GetWidth() const noexcept;
		int GetHeight() const noexcept;

		IBitmap(const IBitmap&) = delete;
		constexpr IBitmap(IBitmap&&) noexcept = default;
		IBitmap& operator=(const IBitmap&) = delete;
		constexpr IBitmap& operator=(IBitmap&&) noexcept = default;

	private:
		bool shouldDestroy = false;
		int cachedWidth = 0, cachedHeight = 0;
	};
}
