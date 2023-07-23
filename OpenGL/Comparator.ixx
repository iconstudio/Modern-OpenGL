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
}
