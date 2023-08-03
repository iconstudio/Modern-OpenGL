export module Glib:System;
import <memory>;
import Glib.Rect;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;
import Glib.Windows.Colour;

export namespace gl
{
	class Blender;
	using win32::Colour;

	namespace system
	{
		struct [[nodiscard]] Descriptor
		{
			Rect viewPort{};
			Colour backgroundColour = win32::colors::Azure;
			Colour borderColour = win32::colors::Black;

			bool staticView = false;
			bool alphaBlend = false;
			bool hiddenSurfaceRemoval = false;
			bool cullingIsClockwise = false;
			bool doubleBuffered = true;
			bool keepAspectRatio = true;
			bool vSync = false;
		};
	}

	/// <summary>
	/// OpenGL Main System
	/// </summary>
	class [[nodiscard]] System
		: private win32::IHandle<win32::native::NativeOGL>
		, public std::enable_shared_from_this<System>
	{
	public:
		using base1 = win32::IHandle<win32::native::NativeOGL>;
		using base2 = std::enable_shared_from_this<System>;
		using Painter = void(*)(win32::GraphicDeviceContext* const&) noexcept;

		System() noexcept;
		~System() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, const system::Descriptor& descriptor) noexcept;

		void SetViewPosition(int x, int y) noexcept;
		void SetViewSize(int width, int height) noexcept;
		void SetViewPort(const Rect& size) noexcept;
		void SetViewPort(Rect&& size) noexcept;
		void SetViewPort(int x, int y, int width, int height) noexcept;
		void UpdateViewPort(int client_hsize, int client_vsize) noexcept;

		void KeepAspectRatio(bool keep_ratio) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

		[[nodiscard]] const Rect& ViewPort() const noexcept;
		[[nodiscard]] int& ViewX() noexcept;
		[[nodiscard]] int& ViewY() noexcept;
		[[nodiscard]] int& ViewWidth() noexcept;
		[[nodiscard]] int& ViewHeight() noexcept;
		[[nodiscard]] const int& ViewX() const noexcept;
		[[nodiscard]] const int& ViewY() const noexcept;
		[[nodiscard]] const int& ViewWidth() const noexcept;
		[[nodiscard]] const int& ViewHeight() const noexcept;
		[[nodiscard]] double AspectRatio() const noexcept;

	private:
		unsigned long _InitializeSystem() noexcept;

		system::Descriptor mySettings{};

		int clientWidth = 0, clientHeight = 0;
		double aspectRatio = 1.0;

		Painter myPainter = nullptr;
		win32::GraphicDeviceContext* nativeContext = nullptr;
		const Blender* myBlender = nullptr;
	};

	[[nodiscard]]
	std::shared_ptr<System> CreateSystem() noexcept;
}
