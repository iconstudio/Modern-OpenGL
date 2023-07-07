export module Glib:DefaultProperty;

export namespace gl
{
	struct [[nodiscard]] default_position_t
	{
		constexpr default_position_t() noexcept = default;
		constexpr ~default_position_t() noexcept = default;
	};

	struct [[nodiscard]] default_resoulution_t
	{
		constexpr default_resoulution_t() noexcept = default;
		constexpr ~default_resoulution_t() noexcept = default;
	};
}
