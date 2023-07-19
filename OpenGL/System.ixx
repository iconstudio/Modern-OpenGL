export module Glib:System;
import <memory>;
import Utility.Monad.Loosen;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;
import Glib.Windows.Colour;

namespace gl
{
	using Painter = void(*)(win32::GraphicDeviceContext* const&) noexcept;

	void SinglePainter(win32::GraphicDeviceContext* const&) noexcept;
	void DoublePainter(win32::GraphicDeviceContext* const&) noexcept;
}

export namespace gl
{
	using win32::Colour;
	class Blender;

	namespace system
	{
		struct [[nodiscard]] Descriptor
		{
			int viewCh, viewCv;

			bool alphaBlend = false;
			bool hiddenSurfaceRemoval = false;
			bool cullingIsClockwise = false;
			bool doubleBuffered = true;
			bool keepRatioAspect = true;
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

		static const win32::Colour DefaultColour;

		System() noexcept;
		~System() noexcept;

		unsigned long Initialize(const win32::IContext& hdc, const system::Descriptor& descriptor) noexcept;

		void SetAspectRatio(bool keep_ratio) noexcept;

		bool Begin(win32::GraphicDeviceContext& painter) noexcept;
		bool End() noexcept;

	private:
		bool keepAspectRatio = true;
		double aspectRatio = 1.0;

		Painter myPainter = nullptr;
		win32::GraphicDeviceContext* nativeContext = nullptr;
		const Blender* myBlender = nullptr;
	};

	using SystemCreation = util::LooseMonad<std::shared_ptr<System>, unsigned long>;

	[[nodiscard]]
	SystemCreation CreateSystem(const win32::IContext& hdc, const system::Descriptor& setup) noexcept;
	[[nodiscard]]
	SystemCreation CreateSystem(const win32::IContext& hdc, system::Descriptor&& setup) noexcept;
}
