export module Glib.Device.IContext;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	class IContext : public IHandle<native::NativeContext>
	{
	public:
		using base = IHandle<native::NativeContext>;

		constexpr IContext() noexcept = default;
		constexpr ~IContext() noexcept = default;

		explicit constexpr IContext(const handle_type& hdc) noexcept
			: base(hdc)
		{}

		explicit constexpr IContext(handle_type&& hdc) noexcept
			: base(std::move(hdc))
		{}

		IContext(const IContext&) = delete;
		IContext& operator=(const IContext&) = delete;
	};
}
