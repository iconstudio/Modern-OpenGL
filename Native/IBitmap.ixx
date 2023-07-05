module;
#include "Internal.hpp"

export module Glib.Device.Resource.Bitmap;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IGraphics;
import Glib.Device.IContext;
import Glib.Device.Colour;

export namespace gl::device::resource
{
	class [[nodiscard]] Bitmap : public IGraphics<Bitmap, native::RawBitmap>
	{
	public:
		using base = IGraphics<Bitmap, native::RawBitmap>;

		[[nodiscard]]
		static Bitmap Load(const FilePath& path) noexcept;
		[[nodiscard]]
		static bool TryLoad(const FilePath& path, Bitmap& output) noexcept;
		[[nodiscard]]
		static Bitmap Load(const int& id) noexcept;
		[[nodiscard]]
		static bool TryLoad(const int& id, Bitmap& output) noexcept;

		explicit Bitmap(const handle_type& handle) noexcept;
		Bitmap(handle_type&& handle) noexcept;
		~Bitmap() noexcept;

		[[nodiscard]] Bitmap Copy(const IContext& context) const noexcept;
		bool TryCopy(const IContext& context, Bitmap& output) const noexcept;

		bool Destroy() noexcept;

		bool Fill(const Colour& color) noexcept;
		void Mirror() noexcept;
		void Flip() noexcept;
		void Rotate(float angle) noexcept;
		void RotateR(float angle) noexcept;
		void RotateL(float angle) noexcept;

		bool Draw(const IWindow& window_handle, const int& dx, const int& dy, const int& srcx = 0, const int& srcy = 0) const noexcept;
		bool Draw(const IContext& render_context, IContext& window_context, const int& dx, const int& dy, const int& srcx = 0, const int& srcy = 0) const noexcept;

		bool GetPixel(const IContext& context, const int& x, const int& y, Colour& output) const;
		int GetWidth() const noexcept;
		int GetHeight() const noexcept;

		Bitmap(const Bitmap&) = delete;
		constexpr Bitmap(Bitmap&&) noexcept = default;
		Bitmap& operator=(const Bitmap&) = delete;
		constexpr Bitmap& operator=(Bitmap&&) noexcept = default;

	protected:
		constexpr Bitmap() noexcept = default;

	private:
		bool shouldDestroy = false;
		int cachedWidth = 0, cachedHeight = 0;
	};
}
