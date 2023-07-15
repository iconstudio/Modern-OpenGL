module;
//#include <gl/GL.h>
export module Glib;
export import <compare>;
export import :System;

export namespace gl
{
	enum class [[nodiscard]] Comparator : unsigned int
	{
		Never = 512,
		Equal = 514,
		NotEqual = 517,
		Less = 513,
		LessOrEqual = 515,
		Greater = 516,
		GreaterOrEqual = 518,
		Always = 519,
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
