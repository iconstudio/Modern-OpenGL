export module Glib.Device.Colour:Implement;
import Glib.Device.Utility;

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

	extern "C" namespace raw_colours
	{
		inline constexpr RawColour COLOR_WHITE = MakeRawColor(255U, 255U, 255U);
		inline constexpr RawColour COLOR_CLOUD = MakeRawColor(224U, 224U, 224U);
		inline constexpr RawColour COLOR_LTGREY = MakeRawColor(211U, 211U, 211U);
		inline constexpr RawColour COLOR_SILVER = MakeRawColor(192U, 192U, 192U);
		inline constexpr RawColour COLOR_GREY = MakeRawColor(128U, 128U, 128U);
		inline constexpr RawColour COLOR_DKGREY = MakeRawColor(64U, 64U, 64U);
		inline constexpr RawColour COLOR_SEMIBLACK = MakeRawColor(32U, 32U, 32U);
		inline constexpr RawColour COLOR_BLACK = MakeRawColor(0U, 0U, 0U);

		inline constexpr RawColour COLOR_RED = MakeRawColor(255U, 0, 0);
		inline constexpr RawColour COLOR_GREEN = MakeRawColor(0, 128U, 0);
		inline constexpr RawColour COLOR_BLUE = MakeRawColor(0, 0, 255U);

		inline constexpr RawColour COLOR_CYAN = MakeRawColor(0, 255U, 255U);
		inline constexpr RawColour COLOR_YELLOW = MakeRawColor(255U, 255U, 0);
		inline constexpr RawColour COLOR_MAGENTA = MakeRawColor(255U, 0, 255U);

		inline constexpr RawColour COLOR_SALMON = MakeRawColor(250U, 128U, 114U);
		inline constexpr RawColour COLOR_MAROON = MakeRawColor(128U, 0, 0);
		inline constexpr RawColour COLOR_GOLD = MakeRawColor(223U, 130U, 20U);
		inline constexpr RawColour COLOR_ORANGE = MakeRawColor(255U, 128U, 0);
		inline constexpr RawColour COLOR_BROWN = MakeRawColor(165U, 42U, 42U);
		inline constexpr RawColour COLOR_TAN = MakeRawColor(210U, 180U, 140U);
		inline constexpr RawColour COLOR_LIME = MakeRawColor(0, 255U, 0);
		inline constexpr RawColour COLOR_NAVY = MakeRawColor(20U, 18U, 149U);
		inline constexpr RawColour COLOR_MIDNIGHTBLUE = MakeRawColor(25U, 25U, 112U);
		inline constexpr RawColour COLOR_PINK = MakeRawColor(255U, 192U, 203U);
		inline constexpr RawColour COLOR_PURPLE = MakeRawColor(128U, 0, 128U);
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
}
