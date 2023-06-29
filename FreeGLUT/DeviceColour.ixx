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
		MakeColor(const RawColour& rgb) noexcept
	{
		return Colour{ rgb };
	}

	[[nodiscard]]
	constexpr Colour
		MakeColor(RawColour&& rgb) noexcept
	{
		return Colour{ std::move(rgb) };
	}

	extern "C" namespace colors
	{
		inline constexpr Colour WHITE = MakeColor(native_colors::COLOR_WHITE);
		inline constexpr Colour CLOUD = MakeColor(native_colors::COLOR_CLOUD);
		inline constexpr Colour LTGREY = MakeColor(native_colors::COLOR_LTGREY);
		inline constexpr Colour GREY = MakeColor(native_colors::COLOR_GREY);
		inline constexpr Colour DKGREY = MakeColor(native_colors::COLOR_DKGREY);
		inline constexpr Colour SEMIBLACK = MakeColor(native_colors::COLOR_SEMIBLACK);
		inline constexpr Colour BLACK = MakeColor(native_colors::COLOR_BLACK);

		inline constexpr Colour RED = MakeColor(native_colors::COLOR_RED);
		inline constexpr Colour MAROON = MakeColor(native_colors::COLOR_MAROON);
		inline constexpr Colour YELLOW = MakeColor(native_colors::COLOR_YELLOW);
		inline constexpr Colour GOLD = MakeColor(native_colors::COLOR_GOLD);

		inline constexpr Colour SALMON = MakeColor(native_colors::COLOR_SALMON);
		inline constexpr Colour ORANGE = MakeColor(native_colors::COLOR_ORANGE);
		inline constexpr Colour BROWN = MakeColor(native_colors::COLOR_BROWN);
		inline constexpr Colour COFFEE = MakeColor(native_colors::COLOR_COFFEE);
		inline constexpr Colour BEIGE = MakeColor(native_colors::COLOR_BEIGE);
		inline constexpr Colour TAN = MakeColor(native_colors::COLOR_TAN);
		inline constexpr Colour KHAKI = MakeColor(native_colors::COLOR_KHAKI);

		inline constexpr Colour OLIVE = MakeColor(native_colors::COLOR_OLIVE);
		inline constexpr Colour OLIVEGREEN = MakeColor(native_colors::COLOR_OLIVEGREEN);
		inline constexpr Colour LAVENDER = MakeColor(native_colors::COLOR_LAVENDER);
		inline constexpr Colour LIME = MakeColor(native_colors::COLOR_LIME);
		inline constexpr Colour GREEN = MakeColor(native_colors::COLOR_GREEN);
		inline constexpr Colour DARKGREEN = MakeColor(native_colors::COLOR_DARKGREEN);
		inline constexpr Colour FORESTGREEN = MakeColor(native_colors::COLOR_FORESTGREEN);
		inline constexpr Colour SEAGREEN = MakeColor(native_colors::COLOR_SEAGREEN);

		inline constexpr Colour STEELBLUE = MakeColor(native_colors::COLOR_STEELBLUE);
		inline constexpr Colour TEAL = MakeColor(native_colors::COLOR_TEAL);
		inline constexpr Colour TURQUOISE = MakeColor(native_colors::COLOR_TURQUOISE);
		inline constexpr Colour CYAN = MakeColor(native_colors::COLOR_CYAN);
		inline constexpr Colour AZURE = MakeColor(native_colors::COLOR_AZURE);
		inline constexpr Colour SKYBLUE = MakeColor(native_colors::COLOR_SKYBLUE);
		inline constexpr Colour BLUE = MakeColor(native_colors::COLOR_BLUE);
		inline constexpr Colour ROYALBLUE = MakeColor(native_colors::COLOR_ROYALBLUE);
		inline constexpr Colour INDIGO = MakeColor(native_colors::COLOR_INDIGO);
		inline constexpr Colour DARKBLUE = MakeColor(native_colors::COLOR_DARKBLUE);
		inline constexpr Colour MIDNIGHTBLUE = MakeColor(native_colors::COLOR_MIDNIGHTBLUE);
		inline constexpr Colour NAVY = MakeColor(native_colors::COLOR_NAVY);

		inline constexpr Colour PURPLE = MakeColor(native_colors::COLOR_PURPLE);
		inline constexpr Colour PINK = MakeColor(native_colors::COLOR_PINK);
		inline constexpr Colour MAGENTA = MakeColor(native_colors::COLOR_MAGENTA);
		inline constexpr Colour VIOLET = MakeColor(native_colors::COLOR_VIOLET);
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
