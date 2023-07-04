export module Glib.Device.IHandle;
import <utility>;
import Utility.Constraints;

export namespace gl::device
{
	template<typename H>
	struct [[nodiscard]] IHandle;

	template<typename H>
	struct [[nodiscard]] IHandle<H*>
	{
		using handle_type = std::remove_reference_t<H>*;
		using pointer_type = H*;
		using value_type = H;

		constexpr IHandle() noexcept = default;
		constexpr ~IHandle() = default;

		constexpr IHandle(IHandle&& other)
			noexcept(util::nothrow_move_constructibles<handle_type>)
			: myHandle(std::exchange(other.myHandle, nullptr))
		{}

		explicit constexpr IHandle(handle_type const& handle) noexcept
			: myHandle(handle)
		{}

		explicit constexpr IHandle(handle_type&& handle) noexcept
			: myHandle(std::exchange(handle, nullptr))
		{}

		explicit constexpr IHandle(nullptr_t) noexcept
			: myHandle(nullptr)
		{}

		constexpr IHandle& operator=(IHandle&& other)
			noexcept(util::nothrow_move_assignables<handle_type>)
		{
			myHandle = std::exchange(other.myHandle, nullptr);
			return *this;
		}

		constexpr IHandle& operator=(const handle_type& handle) noexcept
		{
			myHandle = handle;
			return *this;
		}

		constexpr IHandle& operator=(handle_type&& handle) noexcept
		{
			myHandle = std::exchange(handle, nullptr);
			return *this;
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) &
			noexcept(util::nothrow_invocables<Fn, handle_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, handle_type&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) const&
			noexcept(util::nothrow_invocables<Fn, const handle_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const handle_type&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) &&
			noexcept(util::nothrow_invocables<Fn, handle_type&&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, handle_type&&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) const&&
			noexcept(util::nothrow_invocables<Fn, const handle_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const handle_type&&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
			requires util::invocables<value_type&, Args&&...>
		constexpr auto Delegate(Fn&& fn, Args&&... args) &
			noexcept(util::nothrow_invocables<Fn, value_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, value_type&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), *myHandle, std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), *myHandle, std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
			requires util::invocables<const value_type&, Args&&...>
		constexpr auto Delegate(Fn&& fn, Args&&... args) const&
			noexcept(util::nothrow_invocables<Fn, const value_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const value_type&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), *myHandle, std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), *myHandle, std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
			requires util::invocables<value_type&&, Args&&...>
		constexpr auto Delegate(Fn&& fn, Args&&... args) &&
			noexcept(util::nothrow_invocables<Fn, value_type&&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, value_type&&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(*myHandle), std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(*myHandle), std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
			requires util::invocables<const value_type&&, Args&&...>
		constexpr auto Delegate(Fn&& fn, Args&&... args) const&&
			noexcept(util::nothrow_invocables<Fn, const value_type&&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const value_type&&>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(*myHandle), std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(*myHandle), std::forward<Args>(args)...);
			}
		}

		[[nodiscard]]
		constexpr handle_type& GetHandle() & noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr handle_type const& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr handle_type&& GetHandle() && noexcept
		{
			return std::move(myHandle);
		}

		[[nodiscard]]
		constexpr handle_type const&& GetHandle() const&& noexcept
		{
			return std::move(myHandle);
		}

		constexpr operator handle_type& () & noexcept
		{
			return myHandle;
		}

		constexpr operator handle_type const& () const& noexcept
		{
			return myHandle;
		}

		constexpr operator handle_type && () && noexcept
		{
			return std::move(myHandle);
		}

		constexpr operator handle_type const&& () const&& noexcept
		{
			return std::move(myHandle);
		}

		[[nodiscard]]
		constexpr bool operator==(const IHandle& other) const noexcept
		{
			return myHandle == other.myHandle;
		}

		[[nodiscard]]
		constexpr bool operator==(handle_type const& handle) const noexcept
		{
			return myHandle == handle;
		}

		IHandle(const IHandle&) = delete;
		IHandle& operator=(const IHandle&) = delete;

		std::remove_reference_t<handle_type> myHandle;
	};

	template<util::movable H>
	struct [[nodiscard]] IHandle<H>
	{
		using handle_type = H;

		constexpr IHandle()
			noexcept(util::nothrow_default_constructibles<handle_type>)
			requires util::default_initializable<handle_type> = default;
		constexpr ~IHandle()
			noexcept(util::nothrow_destructibles<handle_type>) = default;

		explicit(util::is_explicit_constructible_v<handle_type>)
			constexpr IHandle(const handle_type& handle)
			noexcept(util::nothrow_copy_constructibles<handle_type>) requires util::copyable<handle_type>
			: myHandle(handle)
		{}

		explicit(util::is_explicit_constructible_v<handle_type>)
			constexpr IHandle(handle_type&& handle)
			noexcept(util::nothrow_move_constructibles<handle_type>)
			: myHandle(std::move(handle))
		{}

		constexpr IHandle& operator=(handle_type&& handle) noexcept
		{
			myHandle = std::move(handle);
			return *this;
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) &
			noexcept(util::nothrow_invocables<Fn, handle_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, handle_type&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) const&
			noexcept(util::nothrow_invocables<Fn, const handle_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const handle_type&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), myHandle, std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) &&
			noexcept(util::nothrow_invocables<Fn, handle_type&&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, handle_type&&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
		}

		template<typename Fn, typename... Args>
		constexpr auto Delegate(Fn&& fn, Args&&... args) const&&
			noexcept(util::nothrow_invocables<Fn, const handle_type&, Args&&...>)
		{
			if constexpr (util::is_same_v<util::invoke_result_t<Fn, const handle_type&&, Args&&...>, void>)
			{
				std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
			else
			{
				return std::invoke(std::forward<Fn>(fn), std::move(myHandle), std::forward<Args>(args)...);
			}
		}

		[[nodiscard]]
		constexpr handle_type& GetHandle() & noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr const handle_type& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr handle_type&& GetHandle() && noexcept
		{
			return std::move(myHandle);
		}

		[[nodiscard]]
		constexpr const handle_type&& GetHandle() const&& noexcept
		{
			return std::move(myHandle);
		}

		explicit constexpr operator handle_type& () & noexcept
		{
			return myHandle;
		}

		explicit constexpr operator const handle_type& () const& noexcept
		{
			return myHandle;
		}

		explicit constexpr operator handle_type && () && noexcept
		{
			return std::move(myHandle);
		}

		explicit constexpr operator const handle_type && () const&& noexcept
		{
			return std::move(myHandle);
		}

		[[nodiscard]]
		constexpr bool operator==(const IHandle& other) const noexcept
		{
			return myHandle == other.myHandle;
		}

		[[nodiscard]]
		constexpr bool operator==(const handle_type& handle) const noexcept
		{
			return myHandle == handle;
		}

		constexpr IHandle(const IHandle&)
			noexcept(util::nothrow_copy_constructibles<handle_type>)
			requires(util::copyable<handle_type>) = default;
		constexpr IHandle(IHandle&&)
			noexcept(util::nothrow_move_constructibles<handle_type>) = default;
		constexpr IHandle& operator=(const IHandle&)
			noexcept(util::nothrow_copy_assignables<handle_type>)
			requires(util::copyable<handle_type>) = default;
		constexpr IHandle& operator=(IHandle&&)
			noexcept(util::nothrow_move_assignables<handle_type>) = default;

		handle_type myHandle;
	};
}
