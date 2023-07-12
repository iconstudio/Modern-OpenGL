export module Glib.GraphicContext;
import Glib.Definitions;
import Glib.Device.IHandle;

export namespace gl
{
	class [[nodiscard]] GLContext
		: public device::IHandle<device::native::NativeOGL>
	{
	public:
		using base = device::IHandle<device::native::NativeOGL>;

		GLContext() noexcept;
		~GLContext() noexcept;

		unsigned long Initialize(const device::IContext& hdc, int view_width, int view_height) noexcept;

		bool Begin(device::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		device::native::NativeContext nativeContext = nullptr;
		bool isDoubleBuffered = false;
	};
}
