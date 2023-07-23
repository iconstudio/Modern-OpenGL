export module Glib:Comparator;
import <cstdint>;

export namespace gl
{
	enum class [[nodiscard]] Comparator : std::uint32_t
	{
		Never = 512U,
		Equal = 514U,
		NotEqual = 517U,
		Less = 513U,
		LessOrEqual = 515U,
		Greater = 516U,
		GreaterOrEqual = 518U,
		Always = 519U,
	};

	inline constexpr Comparator Never = Comparator::Never;
	inline constexpr Comparator Equal = Comparator::Equal;
	inline constexpr Comparator NotEqual = Comparator::NotEqual;
	inline constexpr Comparator Less = Comparator::Less;
	inline constexpr Comparator LessOrEqual = Comparator::LessOrEqual;
	inline constexpr Comparator Greater = Comparator::Greater;
	inline constexpr Comparator GreaterOrEqual = Comparator::GreaterOrEqual;
	inline constexpr Comparator Always = Comparator::Always;
}
