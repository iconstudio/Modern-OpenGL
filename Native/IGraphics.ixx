export module Glib.Device.IGraphics;
import <utility>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	struct [[nodiscard]] nullifier_t
	{
		constexpr nullifier_t() noexcept = default;
	};

	inline constexpr nullifier_t nullifier{};

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

		bool Destroy() noexcept(noexcept(_Cast()->Destroy()))
		{
			return _Cast()->Destroy();
		}

		IGraphics(const IGraphics&) = delete;
		constexpr IGraphics(IGraphics&&) noexcept = default;
		IGraphics& operator=(const IGraphics&&) = delete;

	protected:
		constexpr IGraphics() noexcept = default;

		constexpr IGraphics(nullifier_t) noexcept
			: base(nullptr)
		{}

		explicit constexpr IGraphics(const handle_type& handle) noexcept
			: base(handle)
		{}

		explicit constexpr IGraphics(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		IGraphics& operator=(nullptr_t) noexcept
		{
			if (nullptr != base::GetHandle())
			{
				_Cast()->Destroy();
				base::operator=(nullptr);
			}

			return *this;
		}

		IGraphics& operator=(nullifier_t) noexcept
		{
			base::operator=(nullptr);
			return *this;
		}

		IGraphics& operator=(const handle_type& handle) noexcept
		{
			if (handle == base::GetHandle())
			{
				return *this;
			}

			if (nullptr != base::GetHandle())
			{
				_Cast()->Destroy();
			}
			base::operator=(handle);

			return *this;
		}

		IGraphics& operator=(IGraphics&& other) noexcept
		{
			if (other.GetHandle() == base::GetHandle())
			{
				return *this;
			}

			if (nullptr != base::GetHandle())
			{
				_Cast()->Destroy();
			}
			base::operator=(std::exchange(other.GetHandle(), nullptr));

			return *this;
		}

		constexpr T* _Cast() noexcept
		{
			static_assert(std::is_base_of_v<IGraphics, T>, "T must be derived from IGraphics");
			static_assert(std::is_base_of_v<base, T>, "T must be derived from IHandle");

			return static_cast<T*>(this);
		}

		constexpr const T* _Cast() const noexcept
		{
			static_assert(std::is_base_of_v<IGraphics, T>, "T must be derived from IGraphics");
			static_assert(std::is_base_of_v<base, T>, "T must be derived from IHandle");

			return static_cast<const T*>(this);
		}
	};
}
