export module Glib.GraphicContext;
import Glib.Definitions;
import Glib.Device.IHandle;

export namespace gl
{
	class GLContext : public device::IHandle<device::native::NativeOGL>
	{
	public:
		GLContext(const device::native::HWND& handle) noexcept;
		~GLContext() noexcept;

	};
}
