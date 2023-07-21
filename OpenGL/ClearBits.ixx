export module Glib:ClearBits;

export namespace gl
{
	enum class [[nodiscard]] Clearance : unsigned int
	{
		Color = 0x00004000,
		Depth = 0x00000100,
		Stencil = 0x00000400,
		DepthStencil = 0x00004004,
		Accum = 0x00000200,
	};

	[[nodiscard]]
	constexpr Clearance operator|(const Clearance& lhs, const Clearance& rhs) noexcept
	{
		return static_cast<Clearance>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
	}

	[[nodiscard]]
	constexpr Clearance operator&(const Clearance& lhs, const Clearance& rhs) noexcept
	{
		return static_cast<Clearance>(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
	}

	[[nodiscard]]
	constexpr Clearance operator^(const Clearance& lhs, const Clearance& rhs) noexcept
	{
		return static_cast<Clearance>(static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs));
	}

	[[nodiscard]]
	constexpr Clearance operator~(const Clearance& lhs) noexcept
	{
		return static_cast<Clearance>(~static_cast<unsigned int>(lhs));
	}

	constexpr Clearance& operator|=(Clearance& lhs, const Clearance& rhs) noexcept
	{
		lhs = static_cast<Clearance>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
		return lhs;
	}

	constexpr Clearance& operator&=(Clearance& lhs, const Clearance& rhs) noexcept
	{
		lhs = static_cast<Clearance>(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
		return lhs;
	}

	constexpr Clearance& operator^=(Clearance& lhs, const Clearance& rhs) noexcept
	{
		lhs = static_cast<Clearance>(static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs));
		return lhs;
	}
}
