export module Glib.Windows.Context.Renderer;
import <type_traits>;
import Glib.Windows.Definitions;
export import Glib.Windows.IContext;

export namespace gl::win32
{
	class [[nodiscard]] GraphicDeviceContext : public IContext
	{
	public:
		using base = IContext;

		GraphicDeviceContext(const native::HWND& handle) noexcept;
		~GraphicDeviceContext() noexcept;

		[[nodiscard]] native::PaintStruct& GetPaintStruct() noexcept;
		[[nodiscard]] const native::PaintStruct& GetPaintStruct() const noexcept;

		GraphicDeviceContext(const GraphicDeviceContext&) = delete;
		GraphicDeviceContext(GraphicDeviceContext&&) = delete;
		GraphicDeviceContext& operator=(const GraphicDeviceContext&) = delete;
		GraphicDeviceContext& operator=(GraphicDeviceContext&&) = delete;

	private:
		native::HWND myWindowHandle = nullptr;
		native::PaintStruct myStatus{};
	};
}
