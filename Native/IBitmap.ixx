module;
#include "Internal.hpp"

export module Glib.Device.Resource.IBitmap;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IGraphics;
import Glib.Device.IWindowHandle;
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

		explicit IBitmap(const handle_type& handle) noexcept;
		explicit IBitmap(handle_type&& handle) noexcept;
		~IBitmap() noexcept;

		[[nodiscard]] IBitmap Copy(const ISurface& context) const noexcept;
		[[nodiscard]] bool TryCopy(const ISurface& context, IBitmap& output) const noexcept;

		bool Destroy() noexcept;

		bool Draw(const IWindowHandle& window_handle, const int& dx, const int& dy, const int& srcx = 0, const int& srcy = 0) const noexcept;
		bool Draw(const ISurface& render_context, const ISurface& window_context, const int& dx, const int& dy, const int& srcx = 0, const int& srcy = 0) const noexcept;

		bool GetPixel(const ISurface& context, const int& x, const int& y, Colour& output) const;
		int GetWidth() const noexcept;
		int GetHeight() const noexcept;

		IBitmap(const IBitmap&) = delete;
		constexpr IBitmap(IBitmap&&) noexcept = default;
		IBitmap& operator=(const IBitmap&) = delete;
		constexpr IBitmap& operator=(IBitmap&&) noexcept = default;

	protected:
		constexpr IBitmap() noexcept = default;

	private:
		bool shouldDestroy = false;
		int cachedWidth = 0, cachedHeight = 0;
	};
}
