export module Glib.Device.IHandle;
import Utility.Constraints;

export namespace gl::device
{
	template<util::movable H>
	struct handle_traits
	{
		using Deleter = void(*)(H&);
	};

	struct [[nodiscard]] IHandle
	{
		constexpr IHandle()
			noexcept(util::nothrow_default_constructibles<H>)
			requires util::default_initializable<H> = default;
		constexpr ~IHandle()
			noexcept(util::nothrow_destructibles<H>) = default;

		explicit(util::is_explicit_constructible_v<H>)
			constexpr IHandle(const H& handle)
			noexcept(util::nothrow_copy_constructibles<H>) requires util::copyable<H>
			: myHandle(handle)
		{}

		explicit(util::is_explicit_constructible_v<H>)
			constexpr IHandle(H&& handle)
			noexcept(util::nothrow_move_constructibles<H>)
			: myHandle(std::move(handle))
		{}

		constexpr IHandle& operator=(H&& handle) noexcept
		{
			myHandle = std::move(handle);
			return *this;
		}

		[[nodiscard]]
		constexpr H& GetHandle() & noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr const H& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr H&& GetHandle() && noexcept
		{
			return std::move(myHandle);
		}

		[[nodiscard]]
		constexpr const H&& GetHandle() const&& noexcept
		{
			return std::move(myHandle);
		}

		explicit constexpr operator H& () & noexcept
		{
			return myHandle;
		}

		explicit constexpr operator const H& () const& noexcept
		{
			return myHandle;
		}

		explicit constexpr operator H && () && noexcept
		{
			return std::move(myHandle);
		}

		explicit constexpr operator const H && () const&& noexcept
		{
			return std::move(myHandle);
		}

		[[nodiscard]]
		constexpr bool operator==(const IHandle& other) const noexcept
		{
			return myHandle == other.myHandle;
		}

		[[nodiscard]]
		constexpr bool operator==(const H& handle) const noexcept
		{
			return myHandle == handle;
		}

		constexpr IHandle(const IHandle&)
			noexcept(util::nothrow_copy_constructibles<H>)
			requires util::copyable<H> = default;
		constexpr IHandle(IHandle&&)
			noexcept(util::nothrow_move_constructibles<H>) = default;
		constexpr IHandle& operator=(const IHandle&)
			noexcept(util::nothrow_copy_assignables<H>)
			requires util::copyable<H> = default;
		constexpr IHandle& operator=(IHandle&&)
			noexcept(util::nothrow_move_assignables<H>) = default;

		H myHandle;
	};
}
