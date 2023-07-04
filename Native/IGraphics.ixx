export module Glib.Device.IGraphics;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	template<typename H>
	class [[nodiscard]] IGraphics : public IHandle<H*>
	{
	public:
		using base = IHandle<H*>;
		using handle_type = base::handle_type;
		using base::GetHandle;

		constexpr IGraphics(nullptr_t) noexcept
			: base(nullptr)
		{}

		virtual constexpr ~IGraphics() noexcept = default;

		virtual bool Destroy() noexcept = 0;

		IGraphics& operator=(nullptr_t) noexcept
		{
			if (nullptr != base::GetHandle())
			{
				Destroy();
				base::operator=(nullptr);
			}

			return *this;
		}

		IGraphics& operator=(IGraphics&& other) noexcept
		{
			if (nullptr != base::GetHandle())
			{
				Destroy();
				base::operator=(other.GetHandle());
			}

			return *this;
		}

		IGraphics(const IGraphics&) = delete;
		constexpr IGraphics(IGraphics&&) noexcept = default;
		IGraphics& operator=(const IGraphics&&) = delete;

	protected:
		constexpr IGraphics() noexcept = default;

		explicit constexpr IGraphics(const handle_type& handle) noexcept
			: base(handle)
		{}

		explicit constexpr IGraphics(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}
	};
}
