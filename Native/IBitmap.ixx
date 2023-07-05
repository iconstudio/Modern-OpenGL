module;
#include "Internal.hpp"

export module Glib.Device.Resource.IBitmap;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IGraphics;
import Glib.Device.IWindowHandle;
import Glib.Device.IContext;
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
		IBitmap(handle_type&& handle) noexcept;
		~IBitmap() noexcept;

		[[nodiscard]] IBitmap Copy(const IContext& context) const noexcept;
		bool TryCopy(const IContext& context, IBitmap& output) const noexcept;

		bool Destroy() noexcept;

		bool Draw(const IWindowHandle& window_handle, const int& dx, const int& dy, const int& srcx = 0, const int& srcy = 0) const noexcept;
		bool Draw(const IContext& render_context, IContext& window_context, const int& dx, const int& dy, const int& srcx = 0, const int& srcy = 0) const noexcept;

		bool GetPixel(const IContext& context, const int& x, const int& y, Colour& output) const;
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
