export module Glib:Utility;
import <cstdint>;
import Glib.Windows.Colour;

export namespace gl
{
	using win32::Colour;

	void SetBackgroundColour(const Colour& colour) noexcept;
	void SetBackgroundColour(Colour&& colour) noexcept;
	void SetBackgroundColour(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b, std::uint8_t& b = 255) noexcept;
}
