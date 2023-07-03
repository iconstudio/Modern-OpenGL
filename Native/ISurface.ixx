export module Glib.Device.ISurface;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	class ISurface : public IHandle<native::NativeSurface>
	{
	public:
		using base = IHandle<native::NativeSurface>;

		constexpr ISurface() noexcept = default;
		constexpr ~ISurface() noexcept = default;

		explicit constexpr ISurface(const handle_type& hdc) noexcept
			: base(hdc)
		{}

		explicit constexpr ISurface(handle_type&& hdc) noexcept
			: base(std::move(hdc))
		{}

		ISurface(const ISurface&) = delete;
		ISurface& operator=(const ISurface&) = delete;
	};
}
