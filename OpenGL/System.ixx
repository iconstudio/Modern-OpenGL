export module Glib:System;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;
import Glib.Windows.Colour;

export namespace gl
{
	using win32::Colour;

	class [[nodiscard]] GLSystem
		: private win32::IHandle<gl::win32::native::NativeOGL>
	{
	public:
		using base = win32::IHandle<gl::win32::native::NativeOGL>;

		GLSystem() noexcept;
		~GLSystem() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, int view_width, int view_height) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		int myPixelFormat = 0;
		bool isDoubleBuffered = false;

		gl::win32::native::NativeContext nativeContext = nullptr;

		static inline constexpr Colour DefaultColour = win32::colors::Black;
	};
}
