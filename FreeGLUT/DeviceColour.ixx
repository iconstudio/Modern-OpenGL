module;
#include "Internal.hpp"
#undef LOBYTE

export module Glib.Device.Colour;
import Glib.Device.Utility;
import <type_traits>;
export import :SystemColors;

export namespace gl::device
{
	using RawColour = COLORREF;

	extern "C" namespace native_colors
	{
		inline constexpr RawColour COLOR_BLACK = RGB(0, 0, 0);
		inline constexpr RawColour COLOR_WHITE = RGB(255, 255, 255);
		inline constexpr RawColour COLOR_GREY = RGB(128, 128, 128);
		inline constexpr RawColour COLOR_LTGREY = RGB(192, 192, 192);
		inline constexpr RawColour COLOR_DKGREY = RGB(64, 64, 64);
		inline constexpr RawColour COLOR_SEMIBLACK = RGB(224, 224, 224);

		inline constexpr RawColour COLOR_SALMON = RGB(255, 128, 128);
		inline constexpr RawColour COLOR_RED = RGB(255, 0, 0);
		inline constexpr RawColour COLOR_MAROON = RGB(128, 0, 0);
		inline constexpr RawColour COLOR_LIME = RGB(0, 255, 0);
		inline constexpr RawColour COLOR_GREEN = RGB(0, 128, 0);
		inline constexpr RawColour COLOR_BLUE = RGB(0, 0, 255);
		inline constexpr RawColour COLOR_NAVY = RGB(20, 18, 149);
		inline constexpr RawColour COLOR_ORANGE = RGB(255, 128, 0);
		inline constexpr RawColour COLOR_YELLOW = RGB(255, 255, 0);
		inline constexpr RawColour COLOR_GOLD = RGB(223, 130, 20);
#undef RGB
	}

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
}
