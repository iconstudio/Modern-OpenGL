export module Glib.Device.IGraphics;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	template<typename T, typename H>
	class [[nodiscard]] IGraphics : public IHandle<H>
	{
	public:
		using base = IHandle<H>;
		using handle_type = base::handle_type;
		using base::GetHandle;

		constexpr IGraphics(nullptr_t) noexcept
			: base(nullptr)
		{}

		constexpr ~IGraphics() noexcept = default;

		IGraphics& operator=(nullptr_t) noexcept
		{
			if (nullptr != base::GetHandle())
			{
				_Cast()->Destroy();
				base::operator=(nullptr);
			}

			return *this;
		}

		IGraphics& operator=(IGraphics&& other) noexcept
		{
			if (nullptr != base::GetHandle())
			{
				_Cast()->Destroy();
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

		constexpr T* const& _Cast() noexcept
		{
			static_assert(std::is_base_of_v<IGraphics, T>, "T must be derived from IGraphics");
			static_assert(std::is_base_of_v<base, T>, "T must be derived from IHandle");

			return static_cast<T*>(this);
		}

		constexpr const T* const& _Cast() const noexcept
		{
			static_assert(std::is_base_of_v<IGraphics, T>, "T must be derived from IGraphics");
			static_assert(std::is_base_of_v<base, T>, "T must be derived from IHandle");

			return static_cast<const T*>(this);
		}
	};
}
