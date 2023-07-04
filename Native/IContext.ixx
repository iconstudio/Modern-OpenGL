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

		explicit constexpr IContext(const handle_type& hdc) noexcept
			: base(hdc)
		{}

		explicit constexpr IContext(handle_type&& hdc) noexcept
			: base(std::move(hdc))
		{}

		bool Destroy() noexcept;
		bool Release() noexcept;
		bool Release(native::HWND& owner) noexcept;

		IContext(const IContext&) = delete;
		IContext& operator=(const IContext&) = delete;
	};
}
