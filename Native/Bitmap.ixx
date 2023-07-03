module;
#include "Internal.hpp"

export module Glib.Device.Bitmap;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device::resource
{
	class [[nodiscard]] BitmapFactory
	{
	public:
		::BITMAP data;
	};

	class [[nodiscard]] Bitmap : public IHandle<native::RawBitmap>
	{
	protected:
		Bitmap(native::RawBitmap&&) noexcept;

	public:
		using base = IHandle<native::RawBitmap>;

#undef LoadBitmap
		[[nodiscard]]
		friend Bitmap LoadBitmap(const FilePath& path) noexcept;
		[[nodiscard]]
		friend bool TryLoadBitmap(const FilePath& path, Bitmap& output) noexcept;
		[[nodiscard]]
		friend Bitmap LoadBitmap(const int& id) noexcept;
		[[nodiscard]]
		friend bool TryLoadBitmap(const int& id, Bitmap& output) noexcept;

		constexpr Bitmap() noexcept = default;

		[[nodiscard]]
		Bitmap Copy() const noexcept;

		[[nodiscard]]
		bool TryCopy(Bitmap& output) const noexcept;

		bool Draw(const native::NativeSurface& hdc, const int& x, const int& y) const noexcept;

		bool Destroy() noexcept;

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept
		{
			return nullptr == GetHandle();
		}

	private:
		::BITMAP data;
		void* myBuffer;
	};
}
