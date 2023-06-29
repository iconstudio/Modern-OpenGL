module;
#include "Internal.hpp"
#include <winrt/Windows.UI.ViewManagement.h>
#undef LOBYTE

export module Glib.Device.Colour;
import Glib.Device.Utility;
import <cstdint>;
import <type_traits>;

export using winrt::Windows::UI::operator==;

export namespace gl::device
{
	// DWORD
	using RawColour = unsigned long;

	[[nodiscard]]
	constexpr RawColour
		MakeRawColor(const unsigned char& r, const unsigned char& g, const unsigned char& b)
		noexcept
	{
		return static_cast<unsigned int>(r | (static_cast<unsigned short>(g) << 8U)) | (static_cast<unsigned int>(b) << 16U);
	}

	[[nodiscard]]
	constexpr RawColour
		MakeRawColor(const unsigned int& r, const unsigned int& g, const unsigned int& b)
		noexcept
	{
		return (r | static_cast<unsigned int>(g << 8U)) | (b << 16U);
	}

	extern "C" namespace native_colors
	{
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
#undef RGB
	}

	[[nodiscard]]
	constexpr unsigned char GetRed(const RawColour& rgb) noexcept
	{
		return LOBYTE(rgb);
	}

	[[nodiscard]]
	constexpr unsigned char GetGreen(const RawColour& rgb) noexcept
	{
		return LOBYTE(static_cast<unsigned short>(rgb) >> 8U);
	}

	[[nodiscard]]
	constexpr unsigned char GetBlue(const RawColour& rgb) noexcept
	{
		return LOBYTE(rgb >> 16U);
	}

	[[nodiscard]]
	constexpr bool IsColorBright(const RawColour& col) noexcept
	{
		return 8 * 128 < static_cast<int>(5 * GetGreen(col) + 2 * GetRed(col) + GetBlue(col));
	}

	// A, R, G, B
	struct [[nodiscard]] Colour : public winrt::Windows::UI::Color
	{
		constexpr Colour() noexcept = default;
		constexpr ~Colour() noexcept = default;

		constexpr Colour(const std::uint8_t& a, const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b) noexcept
			: winrt::Windows::UI::Color(a, r, g, b)
		{}

		constexpr Colour(RawColour rgb) noexcept
			: winrt::Windows::UI::Color(GetRed(rgb), GetGreen(rgb), GetBlue(rgb))
		{}

		[[nodiscard]]
		constexpr RawColour ToRaw() const noexcept
		{
			return MakeRawColor(R, G, B);
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
