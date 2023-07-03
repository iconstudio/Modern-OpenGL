module;
#include "Internal.hpp"

export module Glib.Device.Resource.Bitmap;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.Resource.IBitmap;

export namespace gl::device::resource
{
	class [[nodiscard]] Bitmap : public Image
	{
	protected:
		Bitmap(native::RawBitmap&&) noexcept;

	public:
		using base = Image;

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
		constexpr bool IsEmpty() const noexcept
		{
			return nullptr == GetHandle();
		}

	private:
		::BITMAP data;
		void* myBuffer;
	};
}
