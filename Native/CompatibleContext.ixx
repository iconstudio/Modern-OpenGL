export module Glib.Device.CompatibleContext;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;
export import Glib.Device.IContext;

export namespace gl::win32
{
	class CompatibleContext : public IContext
	{
	public:
		using base = IContext;

		constexpr CompatibleContext(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		constexpr CompatibleContext(base&& handle) noexcept
			: base(std::move(handle))
		{}

		~CompatibleContext() noexcept;

		constexpr operator handle_type& () & noexcept
		{
			return GetHandle();
		}

		constexpr operator const handle_type& () const& noexcept
		{
			return GetHandle();
		}

		constexpr operator handle_type && () && noexcept
		{
			return std::move(GetHandle());
		}

		constexpr operator const handle_type && () const&& noexcept
		{
			return std::move(GetHandle());
		}

		CompatibleContext(const CompatibleContext&) = delete;
		CompatibleContext(CompatibleContext&&) = delete;
		CompatibleContext& operator=(const CompatibleContext&) = delete;
		CompatibleContext& operator=(CompatibleContext&&) = delete;
	};
}
