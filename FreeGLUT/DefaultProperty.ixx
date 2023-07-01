export module Glib.DefaultProperty;
import Utility.Constraints;

export namespace gl
{
	template<util::notvoids T>
	struct [[nodiscard]] default_property_t
	{
		constexpr default_property_t()
			noexcept(util::nothrow_default_constructibles<T>)
			requires(util::default_initializable<T>) = default;
		constexpr ~default_property_t()
			noexcept(util::nothrow_destructibles<T>) = default;

		template<typename U>
		constexpr default_property_t(U&& pass)
			noexcept(util::nothrow_constructibles<U&&, T>)
			: value(static_cast<U&&>(pass))
		{}

		constexpr operator T& () & noexcept
		{
			return value;
		}

		template<typename U>
			requires util::assignable_from<T, U>
		constexpr default_property_t& operator=(U&& v)
			noexcept(util::nothrow_assignables<U&&, T>)
		{
			value = static_cast<U&&>(v);

			return *this;
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
		constexpr bool operator==(const T& rhs) const noexcept
		{
			return value == rhs;
		}

		constexpr default_property_t(const default_property_t&) noexcept = default;
		constexpr default_property_t& operator=(const default_property_t&) noexcept = default;
		constexpr default_property_t(default_property_t&&) noexcept = default;
		constexpr default_property_t& operator=(default_property_t&&) noexcept = default;
		constexpr bool operator==(const default_property_t&) const noexcept = default;

		T value;
	};

	template<typename T>
	default_property_t(T) -> default_property_t<T>;

	template<typename T>
	inline constexpr default_property_t<T> default_property{};
}
