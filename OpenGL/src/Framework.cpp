module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#undef CreateWindow
#undef CreateWindowEx

module Glib.Framework;
import <exception>;
import Utility.Monad;
import Glib.Display;
import Glib.Windows.Context;
import Glib.Windows.Context.Renderer;
import Glib.Windows.Client;
import Glib.Windows.Client.Factory;

void ReadyDisplay() noexcept;

gl::framework::InitError
gl::Framework::Initialize(const gl::framework::Descriptor& setup)
{
	ReadyDisplay();

	try
	{
		gl::win32::WindowStyle style = gl::win32::styles::Default;

		if (!setup.isResizable)
		{
			style = gl::win32::styles::Plain;
		}

		myInstance = gl::win32::CreateWindowEx<L"ManagedWindow">(setup.title, setup.wx, setup.wy, setup.ww, setup.wh, 4, style);
		myInstance->SetPowerSave(setup.isPowersave);
	}
	catch (const std::exception& e)
	{
		std::printf("Creating Window Error: '%s'", e.what());

		return framework::InitError::FailedOnCreatingWindow;
	}

	glSystem = gl::CreateSystem();
	if (!glSystem)
	{
		std::printf("Creating OpenGL System Error\n");

		return framework::InitError::FailedOnCreatingSystem;
	}

	const gl::system::Descriptor& gl_descriptor = setup.glDescriptor;
	if (unsigned long check = glSystem->Initialize(myInstance->AcquireContext(), gl_descriptor); 0 != check)
	{
		std::printf("Pixel Formatting Error: %lu\n", check);

		return framework::InitError::FailedOnSettingPixelFormat;
	}

	glSystem->UpdateViewPort(setup.ww, setup.wh);

	AddEventHandler(gl::win32::EventID::Resize
		, [this](gl::win32::ManagedWindow& window, unsigned long long, long long lparam) {
		unsigned int width = LOWORD(lparam);
		unsigned int height = HIWORD(lparam);
		glSystem->UpdateViewPort(width, height);
		window.ClearWindow();
	});

	SetRenderer(setup.renderer);

	using enum gl::win32::managed_window::AwakeResult;
	const auto awakenening = myInstance->Awake();

	if (awakenening != Success)
	{
		//util::Println("Failed on awakening. (code: {}).", static_cast<int>(awakenening));

		//std::rethrow_exception(myInstance->GetException());
		return framework::InitError::FailedOnStartup;
	}

	return framework::InitError::Success;
}

gl::framework::InitError
gl::Framework::Initialize()
{
	return Initialize(framework::MakeDefaultDescriptor());
}

void
gl::Framework::Run()
noexcept
{
	myInstance->Start();
}

void
gl::Framework::AddEventHandler(gl::win32::EventID id, const event_handler_t& procedure)
noexcept
{
	myInstance->AddEventHandler(id, procedure);
}

void
gl::Framework::AddEventHandler(gl::win32::EventID id, event_handler_t&& procedure)
noexcept
{
	myInstance->AddEventHandler(id, std::move(procedure));
}

void
gl::Framework::RemoveEventHandler(gl::win32::EventID id)
noexcept
{
	myInstance->RemoveEventHandler(id);
}

void
gl::Framework::SetRenderer(gl::RenderDelegate handler)
noexcept
{
	myInstance->SetRenderer(
		[this, localRenderer = std::move(handler)](
		[[maybe_unused]] ManagedWindow& window,
		gl::win32::IContext& ctx) {

		glSystem->Begin(ctx);
		localRenderer();
		glSystem->End();
	});
}

gl::Framework::handle_t&
gl::Framework::GetHandle()
noexcept
{
	return *(myInstance.get());
}

const gl::Framework::handle_t&
gl::Framework::GetHandle()
const noexcept
{
	return *(myInstance.get());
}

void ReadyDisplay() noexcept
{
	gl::display::dpi::SetDPIAware(true);

	//constexpr int col_indices[] = { COLOR_WINDOW };
	//constexpr unsigned long colors[] = { RGB(255, 255, 255) };
	//::SetSysColors(1, col_indices, colors);

	if (gl::display::IsDimmingMode())
	{
		std::puts("Dark Mode");
	}
	else
	{
		std::puts("Light Mode");
	}
}

std::shared_ptr<gl::Framework>
gl::CreateFramework()
noexcept
{
	return std::make_shared<Framework>();
}

void
gl::framework::DefaultRenderer()
noexcept
{}

gl::framework::Descriptor
gl::framework::MakeDefaultDescriptor() noexcept
{
	return Descriptor
	{
		.glDescriptor = gl::system::Descriptor
		{
			.viewPort = gl::Rect{ 0, 0, 800, 600 },
		},
		.title = L"FreeGLUT",
		.wx = static_cast<int>(0x80000000), // CW_USEDEFAULT
		.wy = 0,
		.ww = 800,
		.wh = 600,
	};
}
