export module Glib:System;
import <memory>;
import Utility.Monad.Loosen;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;
import Glib.Windows.Colour;

export namespace gl
{
	using win32::Colour;

	namespace system
	{
		struct [[nodiscard]] Descriptor
		{
			int viewCx, viewCy;

			bool keepRatioAspect = true;
		};
	}

	/// <summary>
	/// OpenGL Main System
	/// </summary>
	class [[nodiscard]] System
		: private win32::IHandle<gl::win32::native::NativeOGL>
	{
	public:
		using base = win32::IHandle<gl::win32::native::NativeOGL>;

		static const win32::Colour DefaultColour;

		System() noexcept;
		~System() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, int view_width, int view_height) noexcept;

		void SetAspectRatio(bool keep_ratio) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		int myPixelFormat = 0;
		bool isDoubleBuffered = false;
		bool keepAspectRatio = true;

		gl::win32::native::NativeContext nativeContext = nullptr;
	};

	using SystemCreation = util::LooseMonad<std::shared_ptr<System>, unsigned long>;

	[[nodiscard]]
	SystemCreation CreateSystem(const win32::IContext& hdc, const system::Descriptor& setup) noexcept;
	[[nodiscard]]
	SystemCreation CreateSystem(const win32::IContext& hdc, system::Descriptor&& setup) noexcept;
}
