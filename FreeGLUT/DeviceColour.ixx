module;
#include "Internal.hpp"
#include <winrt/Windows.UI.ViewManagement.h>
#undef LOBYTE

export module Glib.Device.Colour;
import <cstdint>;
import <type_traits>;
export import :RawColour;

export using winrt::Windows::UI::operator==;
using NativeColor = winrt::Windows::UI::Color;

export namespace gl::device
{
	// A, R, G, B
	struct [[nodiscard]] Colour : public NativeColor
	{
		constexpr Colour() noexcept = default;
		constexpr ~Colour() noexcept = default;

		constexpr Colour(const std::uint8_t& a, const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b) noexcept
			: NativeColor(a, r, g, b)
		{}

		constexpr Colour(const NativeColor& argb) noexcept
			: NativeColor(argb)
		{}

		constexpr Colour(NativeColor&& argb) noexcept
			: NativeColor(std::move(argb))
		{}

		constexpr Colour(const RawColour& rgb) noexcept
			: NativeColor(0xFF, GetRed(rgb), GetGreen(rgb), GetBlue(rgb))
		{}

		[[nodiscard]]
		constexpr RawColour ToRaw() const noexcept
		{
			return MakeRawColor(R, G, B);
		}

		constexpr Colour& operator=(const RawColour& color) noexcept
		{
			swap(Colour{ color });

			return *this;
		}

		constexpr Colour& operator=(RawColour&& color) noexcept
		{
			swap(Colour{ std::move(color) });

			return *this;
		}

		constexpr Colour& operator=(const NativeColor& color) noexcept
		{
			swap(Colour{ color.A, color.R, color.G, color.B });

			return *this;
		}

		constexpr Colour& operator=(NativeColor&& color) noexcept
		{
			swap(Colour{ std::move(color.A), std::move(color.R), std::move(color.G), std::move(color.B) });

			return *this;
		}

		constexpr void swap(Colour& other) noexcept
		{
			std::swap(A, other.A);
			std::swap(R, other.R);
			std::swap(G, other.G);
			std::swap(B, other.B);
		}

		constexpr void swap(const Colour&& other) noexcept
		{
			A = std::move(other.A);
			R = std::move(other.R);
			G = std::move(other.G);
			B = std::move(other.B);
		}

		inline friend constexpr void swap(Colour& lhs, Colour& rhs) noexcept
		{
			lhs.swap(rhs);
		}

		[[nodiscard]]
		inline friend constexpr bool IsColorBright(const Colour& col) noexcept
		{
			return 8 * 128 < static_cast<int>(5 * col.G + 2 * col.R + col.B);
		}

		constexpr Colour(const Colour&) noexcept = default;
		constexpr Colour(Colour&&) noexcept = default;
		constexpr Colour& operator=(const Colour&) noexcept = default;
		constexpr Colour& operator=(Colour&&) noexcept = default;
	};

	[[nodiscard]]
	constexpr Colour
		MakeColor(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b)
		noexcept
	{
		return Colour{ 0xFFU, r, g, b };
	}

	extern "C" namespace colors
	{
		inline constexpr Colour WHITE = MakeColor(255U, 255U, 255U);

		inline constexpr RawColour COLOR_WHITE = MakeRawColor(255U, 255U, 255U);
		inline constexpr RawColour COLOR_CLOUD = MakeRawColor(224U, 224U, 224U);
		inline constexpr RawColour COLOR_LTGREY = MakeRawColor(192U, 192U, 192U);
		inline constexpr RawColour COLOR_GREY = MakeRawColor(128U, 128U, 128U);
		inline constexpr RawColour COLOR_DKGREY = MakeRawColor(64U, 64U, 64U);
		inline constexpr RawColour COLOR_SEMIBLACK = MakeRawColor(32U, 32U, 32U);
		inline constexpr RawColour COLOR_BLACK = MakeRawColor(0U, 0U, 0U);

		inline constexpr RawColour COLOR_SALMON = MakeRawColor(255U, 128U, 128U);
		inline constexpr RawColour COLOR_RED = MakeRawColor(255U, 0, 0);
		inline constexpr RawColour COLOR_MAROON = MakeRawColor(128U, 0, 0);
		inline constexpr RawColour COLOR_LIME = MakeRawColor(0, 255U, 0);
		inline constexpr RawColour COLOR_GREEN = MakeRawColor(0, 128U, 0);
		inline constexpr RawColour COLOR_BLUE = MakeRawColor(0, 0, 255U);
		inline constexpr RawColour COLOR_NAVY = MakeRawColor(20U, 18U, 149U);
		inline constexpr RawColour COLOR_ORANGE = MakeRawColor(255U, 128U, 0);
		inline constexpr RawColour COLOR_YELLOW = MakeRawColor(255U, 255U, 0);
		inline constexpr RawColour COLOR_GOLD = MakeRawColor(223U, 130U, 20U);
	}

	[[nodiscard]]
	constexpr std::uint8_t GetRed(const Colour& argb) noexcept
	{
		return argb.R;
	}

	[[nodiscard]]
	constexpr std::uint8_t GetGreen(const Colour& argb) noexcept
	{
		return argb.G;
	}

	[[nodiscard]]
	constexpr std::uint8_t GetBlue(const Colour& argb) noexcept
	{
		return argb.B;
	}

	[[nodiscard]]
	constexpr std::uint8_t GetAlpha(const Colour& argb) noexcept
	{
		return argb.A;
	}
}
