export module Glib.Device.Context.Renderer;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IContext;

export namespace gl::device
{
	class [[nodiscard]] RenderingContext : public IContext
	{
	public:
		using base = IContext;

		RenderingContext(const native::HWND& handle) noexcept;
		~RenderingContext() noexcept;

		RenderingContext(const RenderingContext&) = delete;
		RenderingContext(RenderingContext&&) = delete;
		RenderingContext& operator=(const RenderingContext&) = delete;
		RenderingContext& operator=(RenderingContext&&) = delete;

	private:
		native::HWND myWindowHandle;
		native::PaintStruct myStatus;
	};
}
