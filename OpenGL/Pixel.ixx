export module Glib:Pixel;
import Glib.Windows.Colour;

export namespace gl
{
	using gl::win32::Colour;

	struct [[nodiscard]] BitmapPixel
	{
		Colour colour;
	};

	struct [[nodiscard]] ScreenPixel
	{
		Colour colour;
		float depth;
	};
}
