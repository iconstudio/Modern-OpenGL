export module Glib.Device.CompatibleContext;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;
import Glib.Device.IContext;

export namespace gl::device
{
	class CompatibleContext : public IHandle<IContext>
	{
	public:
		using base = IHandle<IContext>;

		constexpr CompatibleContext(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		constexpr CompatibleContext(base&& handle) noexcept
			: base(std::move(handle))
		{}

		~CompatibleContext() noexcept;

		constexpr operator native::NativeContext& () & noexcept
		{
			return GetHandle().GetHandle();
		}

		constexpr operator const native::NativeContext& () const& noexcept
		{
			return GetHandle().GetHandle();
		}

		constexpr operator native::NativeContext && () && noexcept
		{
			return std::move(GetHandle()).GetHandle();
		}

		constexpr operator const native::NativeContext && () const&& noexcept
		{
			return std::move(GetHandle()).GetHandle();
		}

		CompatibleContext(const CompatibleContext&) = delete;
		CompatibleContext(CompatibleContext&&) = delete;
		CompatibleContext& operator=(const CompatibleContext&) = delete;
		CompatibleContext& operator=(CompatibleContext&&) = delete;
	};
}
