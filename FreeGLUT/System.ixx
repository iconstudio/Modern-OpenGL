export module Glib:System;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;
import Glib.Windows.Colour;

export namespace gl
{
	class [[nodiscard]] GLSystem
		: public win32::IHandle<gl::win32::native::NativeOGL>
	{
	public:
		using base = win32::IHandle<gl::win32::native::NativeOGL>;

		GLSystem() noexcept;
		~GLSystem() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, int view_width, int view_height) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		gl::win32::native::NativeContext nativeContext = nullptr;
		gl::win32::Colour backgroundColour = gl::win32::colors::ForrestGreen;
		bool isDoubleBuffered = false;
	};
}
