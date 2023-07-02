export module Glib.Device.Colour:Implement;
import <cstdint>;
import Glib.Device.Utility;

export namespace gl::device
{
	/// <summary>
	/// 32-bit value, where the least-significant 8 bits are blue, the next 8 bits are green, and the next 8 bits are red.
	/// </summary>
	/// <remarks>
	/// This is <see cref="COLORREF"/> by Windows API.
	/// </remarks>
	using RawRGB = std::uint32_t;
	/// <summary>
	/// 32-bit value, where the least-significant 8 bits are blue, the next 8 bits are green, the next 8 bits are red, and the next 8 bits are alpha.
		/// </summary>
	/// <remarks>
	/// This is <see cref="Windows::UI::Color"/> by WinUI 3.
	/// </remarks>
	using RawARGB = std::uint32_t;

	[[nodiscard]]
	constexpr RawRGB
		MakeRawColor(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b)
		noexcept
	{
		return static_cast<std::uint32_t>(r | (static_cast<unsigned short>(g) << 8U)) | (static_cast<std::uint32_t>(b) << 16U);
	}

	[[nodiscard]]
	constexpr RawRGB
		MakeRawColor(const std::uint32_t& r, const std::uint32_t& g, const std::uint32_t& b)
		noexcept
	{
		return (r | static_cast<std::uint32_t>(g << 8U)) | (b << 16U);
	}

	extern "C" namespace raw_colours
	{
		inline constexpr RawRGB COLOR_WHITE = MakeRawColor(255U, 255U, 255U);
		inline constexpr RawRGB COLOR_CLOUD = MakeRawColor(224U, 224U, 224U);
		inline constexpr RawRGB COLOR_LTGREY = MakeRawColor(211U, 211U, 211U);
		inline constexpr RawRGB COLOR_SILVER = MakeRawColor(192U, 192U, 192U);
		inline constexpr RawRGB COLOR_GREY = MakeRawColor(128U, 128U, 128U);
		inline constexpr RawRGB COLOR_DKGREY = MakeRawColor(64U, 64U, 64U);
		inline constexpr RawRGB COLOR_SEMIBLACK = MakeRawColor(32U, 32U, 32U);
		inline constexpr RawRGB COLOR_BLACK = MakeRawColor(0U, 0U, 0U);

		inline constexpr RawRGB COLOR_RED = MakeRawColor(255U, 0, 0);
		inline constexpr RawRGB COLOR_GREEN = MakeRawColor(0, 128U, 0);
		inline constexpr RawRGB COLOR_BLUE = MakeRawColor(0, 0, 255U);

		inline constexpr RawRGB COLOR_CYAN = MakeRawColor(0, 255U, 255U);
		inline constexpr RawRGB COLOR_YELLOW = MakeRawColor(255U, 255U, 0);
		inline constexpr RawRGB COLOR_MAGENTA = MakeRawColor(255U, 0, 255U);

		inline constexpr RawRGB COLOR_SALMON = MakeRawColor(250U, 128U, 114U);
		inline constexpr RawRGB COLOR_MAROON = MakeRawColor(128U, 0, 0);
		inline constexpr RawRGB COLOR_GOLD = MakeRawColor(223U, 130U, 20U);
		inline constexpr RawRGB COLOR_ORANGE = MakeRawColor(255U, 128U, 0);
		inline constexpr RawRGB COLOR_BROWN = MakeRawColor(165U, 42U, 42U);
		inline constexpr RawRGB COLOR_TAN = MakeRawColor(210U, 180U, 140U);
		inline constexpr RawRGB COLOR_LIME = MakeRawColor(0, 255U, 0);
		inline constexpr RawRGB COLOR_NAVY = MakeRawColor(20U, 18U, 149U);
		inline constexpr RawRGB COLOR_MIDNIGHTBLUE = MakeRawColor(25U, 25U, 112U);
		inline constexpr RawRGB COLOR_PINK = MakeRawColor(255U, 192U, 203U);
		inline constexpr RawRGB COLOR_PURPLE = MakeRawColor(128U, 0, 128U);
	}

	[[nodiscard]]
	constexpr std::uint8_t GetRed(const RawRGB& rgb) noexcept
	{
		return LOBYTE(rgb);
	}

	[[nodiscard]]
	constexpr std::uint8_t GetGreen(const RawRGB& rgb) noexcept
	{
		return LOBYTE(static_cast<unsigned short>(rgb) >> 8U);
	}

	[[nodiscard]]
	constexpr std::uint8_t GetBlue(const RawRGB& rgb) noexcept
	{
		return LOBYTE(rgb >> 16U);
	}

	[[nodiscard]]
	constexpr bool IsColorBright(const RawRGB& col) noexcept
	{
		return 8 * 128 < static_cast<int>(5 * GetGreen(col) + 2 * GetRed(col) + GetBlue(col));
	}
}
