export module Glib.Device.IContext;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	class IContext : public IHandle<native::NativeContext>
	{
	private:
		struct [[nodiscard]] GraphicState
		{
			void* object = nullptr;
		};

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

		CompatibleContext CreateCompatibleContext() const noexcept;
		resource::CompatibleBitmap CreateCompatibleBitmap(const int& width, const int& height) const noexcept;
		bool Destroy() noexcept;
		bool Release() noexcept;
		bool Release(native::HWND& owner) noexcept;

		GraphicState Select(const resource::ColorBrush& obj) const noexcept;
		GraphicState Select(const resource::Pen& obj) const noexcept;
		GraphicState Select(const resource::Palette& obj) const noexcept;
		GraphicState Select(const resource::Bitmap& obj) const noexcept;
		GraphicState Select(const resource::CompatibleBitmap& obj) const noexcept;
		void Select(GraphicState& previous) const noexcept;

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
