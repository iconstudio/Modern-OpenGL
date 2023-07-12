export module Glib.GraphicContext;
import Glib.Definitions;
import Glib.Device.IHandle;

export namespace gl
{
	class GLContext : public device::IHandle<device::native::NativeOGL>
	{
	public:
		GLContext() noexcept = default;
		~GLContext() noexcept = default;

		bool Initialize(const device::IContext& hdc) noexcept;

		bool Begin(device::GraphicDeviceContext& painter) noexcept;
		void End() noexcept;
	};
}
