export module Glib.Device.Context.Renderer;
import <type_traits>;
import Glib.Definitions;
export import Glib.Device.IContext;

export namespace gl::device
{
	class [[nodiscard]] GraphicDeviceContext : public IContext
	{
	public:
		using base = IContext;

		GraphicDeviceContext(const native::HWND& handle) noexcept;
		~GraphicDeviceContext() noexcept;

		native::PaintStruct& GetStatus() noexcept;
		const native::PaintStruct& GetStatus() const noexcept;

		GraphicDeviceContext(const GraphicDeviceContext&) = delete;
		GraphicDeviceContext(GraphicDeviceContext&&) = delete;
		GraphicDeviceContext& operator=(const GraphicDeviceContext&) = delete;
		GraphicDeviceContext& operator=(GraphicDeviceContext&&) = delete;

	private:
		native::HWND myWindowHandle = nullptr;
		native::PaintStruct myStatus{};
	};
}
