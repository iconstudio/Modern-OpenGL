export module Glib.Device.IHandle;
import Utility.Constraints;

export namespace gl::device
{
	template<util::movable H>
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

		template<typename Fn>
		constexpr auto Delegate(Fn&& fn) &
			noexcept(util::nothrow_invocables<Fn, H&>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, H&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), myHandle);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), myHandle);
			}
		}

		template<typename Fn>
		constexpr auto Delegate(Fn&& fn) const&
			noexcept(util::nothrow_invocables<Fn, const H&>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const H&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), myHandle);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), myHandle);
			}
		}

		template<typename Fn>
		constexpr auto Delegate(Fn&& fn) &&
			noexcept(util::nothrow_invocables<Fn, H&&>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, H&&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(myHandle));
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(myHandle));
			}
		}

		template<typename Fn>
		constexpr auto Delegate(Fn&& fn) const&&
			noexcept(util::nothrow_invocables<Fn, const H&>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const H&&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(myHandle));
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(myHandle));
			}
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
