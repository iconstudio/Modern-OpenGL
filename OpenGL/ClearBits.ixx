export module Glib:ClearBits;
import <cstdint>;

export namespace gl
{
	enum class [[nodiscard]] Clearance : std::uint32_t
	{
		Color = 0x00004000U,
		Depth = 0x00000100U,
		Accum = 0x00000200U,
		Stencil = 0x00000400U,
		DepthStencil = 0x00004004U,
	};

	[[nodiscard]]
	constexpr Clearance operator|(const Clearance& lhs, const Clearance& rhs) noexcept
	{
		return static_cast<Clearance>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
	}

	[[nodiscard]]
	constexpr Clearance operator&(const Clearance& lhs, const Clearance& rhs) noexcept
	{
		return static_cast<Clearance>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
	}

	[[nodiscard]]
	constexpr Clearance operator^(const Clearance& lhs, const Clearance& rhs) noexcept
	{
		return static_cast<Clearance>(static_cast<std::uint32_t>(lhs) ^ static_cast<std::uint32_t>(rhs));
	}

	[[nodiscard]]
	constexpr Clearance operator~(const Clearance& lhs) noexcept
	{
		return static_cast<Clearance>(~static_cast<std::uint32_t>(lhs));
	}

	constexpr Clearance& operator|=(Clearance& lhs, const Clearance& rhs) noexcept
	{
		lhs = static_cast<Clearance>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
		return lhs;
	}

	constexpr Clearance& operator&=(Clearance& lhs, const Clearance& rhs) noexcept
	{
		lhs = static_cast<Clearance>(static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs));
		return lhs;
	}

	constexpr Clearance& operator^=(Clearance& lhs, const Clearance& rhs) noexcept
	{
		lhs = static_cast<Clearance>(static_cast<std::uint32_t>(lhs) ^ static_cast<std::uint32_t>(rhs));
		return lhs;
	}
}
