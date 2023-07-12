export module Glib.GraphicContext;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;

export namespace gl
{
	class [[nodiscard]] GLContext
		: public win32::IHandle<gl::win32::native::NativeOGL>
	{
	public:
		using base = win32::IHandle<gl::win32::native::NativeOGL>;

		GLContext() noexcept;
		~GLContext() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, int view_width, int view_height) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		gl::win32::native::NativeContext nativeContext = nullptr;
		bool isDoubleBuffered = false;
	};
}
