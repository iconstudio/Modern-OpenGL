export module Glib:System;
import <memory>;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;
import Glib.Windows.Colour;

export namespace gl
{
	using win32::Colour;

	namespace system
	{
		struct Descriptor
		{
			int viewCx, viewCy;

			bool keepRatioAspect = true;
		};
	}

	class [[nodiscard]] System
		: private win32::IHandle<gl::win32::native::NativeOGL>
	{
	public:
		using base = win32::IHandle<gl::win32::native::NativeOGL>;

		static const win32::Colour DefaultColour;

		System() noexcept;
		~System() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, int view_width, int view_height) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		int myPixelFormat = 0;
		bool isDoubleBuffered = false;

		gl::win32::native::NativeContext nativeContext = nullptr;
	};

	std::shared_ptr<System> CreateSystem(const system::Descriptor& setup) noexcept;
	std::shared_ptr<System> CreateSystem(system::Descriptor&& setup) noexcept;
}
