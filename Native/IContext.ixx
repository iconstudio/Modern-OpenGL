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

		constexpr IContext(handle_type&& hdc) noexcept
			: base(std::move(hdc))
			, shouldDestroy(true)
		{}

		~IContext() noexcept;

		IContext CreateCompatibleContext() const noexcept;
		resource::IBitmap CreateCompatibleBitmap(const int& width, const int& height) const noexcept;
		bool Destroy() noexcept;
		bool Release() noexcept;
		bool Release(native::HWND& owner) noexcept;

		constexpr operator native::NativeContext& () & noexcept
		{
			return GetHandle();
		}

		constexpr operator const native::NativeContext& () const& noexcept
		{
			return GetHandle();
		}

		constexpr operator native::NativeContext && () && noexcept
		{
			return std::move(GetHandle());
		}

		constexpr operator const native::NativeContext && () const&& noexcept
		{
			return std::move(GetHandle());
		}

		IContext(const IContext&) = delete;
		constexpr IContext(IContext&&) noexcept = default;
		IContext& operator=(const IContext&) = delete;
		constexpr IContext& operator=(IContext&&) noexcept = default;

	private:
		bool shouldDestroy = false;
	};
}
