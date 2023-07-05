export module Glib.Device.Resource.CompatibleBitmap;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;
import Glib.Device.Resource.IBitmap;

export namespace gl::device::resource
{
	class CompatibleBitmap : public IBitmap
	{
	public:
		using base = IBitmap;

		constexpr CompatibleBitmap(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		~CompatibleBitmap() noexcept;

		explicit constexpr operator handle_type& () & noexcept
		{
			return GetHandle();
		}

		explicit constexpr operator const handle_type& () const& noexcept
		{
			return GetHandle();
		}

		explicit constexpr operator handle_type && () && noexcept
		{
			return std::move(GetHandle());
		}

		explicit constexpr operator const handle_type && () const&& noexcept
		{
			return std::move(GetHandle());
		}

		CompatibleBitmap(const CompatibleBitmap&) = delete;
		constexpr CompatibleBitmap(CompatibleBitmap&&) noexcept = default;
		CompatibleBitmap& operator=(const CompatibleBitmap&) = delete;
		constexpr CompatibleBitmap& operator=(CompatibleBitmap&&) noexcept = default;
	};
}
