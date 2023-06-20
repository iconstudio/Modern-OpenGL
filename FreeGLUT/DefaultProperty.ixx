export module Glib.DefaultProperty;

export namespace gl
{
	template<typename T>
	struct [[nodiscard]] default_property_t;

	template<typename T>
	struct [[nodiscard]] default_property_t
	{
		constexpr default_property_t() noexcept = default;
		constexpr ~default_property_t() noexcept = default;

		template<typename U>
		constexpr default_property_t(U&& pass) noexcept
			: value(static_cast<U&&>(pass))
		{}

		constexpr operator T& () & noexcept
		{
			return value;
		}

		constexpr operator T const& () const& noexcept
		{
			return value;
		}

		constexpr operator T && () && noexcept
		{
			return static_cast<T&&>(value);
		}

		constexpr operator T const&& () const&& noexcept
		{
			return static_cast<T&&>(value);
		}

		[[nodiscard]]
		constexpr bool operator==(const default_property_t& rhs) const
		{
			if (this == &rhs)
			{
				return true;
			}

			return false;
		}

		constexpr default_property_t(const default_property_t&) noexcept = default;
		constexpr default_property_t& operator=(const default_property_t&) noexcept = default;
		constexpr default_property_t(default_property_t&&) noexcept = default;
		constexpr default_property_t& operator=(default_property_t&&) noexcept = default;

		T value;
	};

	template<>
	struct [[nodiscard]] default_property_t<void>
	{
		constexpr default_property_t() noexcept = default;
		constexpr ~default_property_t() noexcept = default;
	};

	template<typename T>
	default_property_t(T) -> default_property_t<T>;

	template<typename T>
	inline constexpr default_property_t<T> default_property{};
}
