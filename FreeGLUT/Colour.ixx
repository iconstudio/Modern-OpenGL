module;
#include "Internal.hpp"
#include <winrt/Windows.UI.ViewManagement.h>
#undef LOBYTE

export module Glib.Device.Colour;
import <cstdint>;
import <type_traits>;
export import :Implement;

export using winrt::Windows::UI::operator==;
export using NativeColor = winrt::Windows::UI::Color;

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

		constexpr Colour(const RawRGB& rgb) noexcept
			: NativeColor(0xFF, GetRed(rgb), GetGreen(rgb), GetBlue(rgb))
		{}

		[[nodiscard]]
		constexpr RawRGB ToRaw() const noexcept
		{
			return MakeRawColor(R, G, B);
		}

		constexpr Colour& operator=(const RawRGB& color) noexcept
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

		constexpr Colour(const Colour&) noexcept = default;
		constexpr Colour(Colour&&) noexcept = default;
		constexpr Colour& operator=(const Colour&) noexcept = default;
		constexpr Colour& operator=(Colour&&) noexcept = default;
	};

	[[nodiscard]]
	constexpr Colour
		MakeColor(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b) noexcept
	{
		return Colour{ 0xFFU, r, g, b };
	}

	[[nodiscard]]
	constexpr Colour
		MakeColor(const NativeColor& argb) noexcept
	{
		return Colour{ argb };
	}

	[[nodiscard]]
	constexpr Colour
		MakeColor(NativeColor&& argb) noexcept
	{
		return Colour{ std::move(argb) };
	}

	[[nodiscard]]
	constexpr Colour
		MakeColor(const RawRGB& rgb) noexcept
	{
		return Colour{ rgb };
	}

	[[nodiscard]]
	constexpr Colour
		MakeColor(RawRGB&& rgb) noexcept
	{
		return Colour{ std::move(rgb) };
	}

	extern "C" namespace colors
	{
		inline constexpr Colour White = MakeColor(raw_colours::COLOR_WHITE);
		inline constexpr Colour Cloud = MakeColor(raw_colours::COLOR_CLOUD);
		inline constexpr Colour LightGray = MakeColor(raw_colours::COLOR_LTGREY);
		inline constexpr Colour LightGrey = LightGray;
		inline constexpr Colour Silver = MakeColor(raw_colours::COLOR_SILVER);
		inline constexpr Colour Gray = MakeColor(raw_colours::COLOR_GREY);
		inline constexpr Colour Grey = Gray;
		inline constexpr Colour DimGray = MakeColor(105U, 105U, 105U);
		inline constexpr Colour DimGrey = DimGray;
		inline constexpr Colour DarkGray = MakeColor(raw_colours::COLOR_DKGREY);
		inline constexpr Colour DarkGrey = DarkGray;
		inline constexpr Colour LightSlateGray = MakeColor(119U, 136U, 153U);
		inline constexpr Colour LightSlateGrey = LightSlateGray;
		inline constexpr Colour SlateGray = MakeColor(112U, 128U, 144U);
		inline constexpr Colour SlateGrey = SlateGray;
		inline constexpr Colour SemiBlack = MakeColor(raw_colours::COLOR_SEMIBLACK);
		inline constexpr Colour Black = MakeColor(raw_colours::COLOR_BLACK);

		inline constexpr Colour Crimson = MakeColor(220U, 20U, 60U);
		inline constexpr Colour Red = MakeColor(raw_colours::COLOR_RED);
		inline constexpr Colour Maroon = MakeColor(raw_colours::COLOR_MAROON);
		inline constexpr Colour Yellow = MakeColor(raw_colours::COLOR_YELLOW);
		inline constexpr Colour Gold = MakeColor(raw_colours::COLOR_GOLD);

		inline constexpr Colour Salmon = MakeColor(raw_colours::COLOR_SALMON);
		inline constexpr Colour Orange = MakeColor(raw_colours::COLOR_ORANGE);
		inline constexpr Colour Brown = MakeColor(raw_colours::COLOR_BROWN);
		inline constexpr Colour CornSilk = MakeColor(255, 248, 220);
		inline constexpr Colour Beige = MakeColor(245, 245, 220);
		inline constexpr Colour Tan = MakeColor(raw_colours::COLOR_TAN);
		inline constexpr Colour Khaki = MakeColor(240U, 230U, 140U);

		inline constexpr Colour Olive = MakeColor(128U, 128U, 0U);
		inline constexpr Colour Lime = MakeColor(raw_colours::COLOR_LIME);
		inline constexpr Colour LightGreen = MakeColor(144U, 238U, 144U);
		inline constexpr Colour PaleGreen = MakeColor(152U, 251U, 152U);
		inline constexpr Colour Green = MakeColor(raw_colours::COLOR_GREEN);
		inline constexpr Colour ForrestGreen = MakeColor(34U, 139U, 34U);
		inline constexpr Colour SeaGreen = MakeColor(46U, 139U, 87U);
		inline constexpr Colour DarkGreen = MakeColor(0U, 100U, 0U);

		inline constexpr Colour Teal = MakeColor(0U, 128U, 128U);
		inline constexpr Colour SteelBlue = MakeColor(70U, 130U, 180U);
		inline constexpr Colour Cyan = MakeColor(raw_colours::COLOR_CYAN);
		inline constexpr Colour PaleAzure = MakeColor(240U, 255U, 255U);
		inline constexpr Colour Azure = MakeColor(0U, 127U, 255U);

		inline constexpr Colour SkyBlue = MakeColor(0U, 191U, 255U);
		inline constexpr Colour MidnightBlue = MakeColor(raw_colours::COLOR_MIDNIGHTBLUE);
		inline constexpr Colour RoyaleBlue = MakeColor(65U, 105U, 225U);

		inline constexpr Colour Blue = MakeColor(raw_colours::COLOR_BLUE);
		inline constexpr Colour MediumBlue = MakeColor(0U, 0U, 205U);
		inline constexpr Colour DarkBlue = MakeColor(0U, 0U, 139U);
		inline constexpr Colour NAVY = MakeColor(raw_colours::COLOR_NAVY);

		inline constexpr Colour Lavender = MakeColor(230U, 230U, 250U);
		inline constexpr Colour Violet = MakeColor(140U, 0U, 255U);
		inline constexpr Colour Purple = MakeColor(raw_colours::COLOR_PURPLE);
		inline constexpr Colour Indigo = MakeColor(148U, 0U, 211U);
		inline constexpr Colour DarkIndigo = MakeColor(75U, 0U, 130U);

		inline constexpr Colour Magenta = MakeColor(raw_colours::COLOR_MAGENTA);
		inline constexpr Colour Pink = MakeColor(raw_colours::COLOR_PINK);
		inline constexpr Colour HotPink = MakeColor(255U, 105U, 180U);
		inline constexpr Colour DeepPink = MakeColor(255U, 20U, 147U);

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

	[[nodiscard]]
	constexpr bool IsColorBright(const Colour& col) noexcept
	{
		return 8 * 128 < static_cast<int>(5 * col.G + 2 * col.R + col.B);
	}
}
