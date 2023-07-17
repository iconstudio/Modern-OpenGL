module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#undef CreateWindow
#undef CreateWindowEx

module Glib.Framework;
import <cstdio>;
import <exception>;
import <format>;
import Glib;
import Glib.Display;
import Glib.Windows.Context;
import Glib.Windows.Context.Renderer;
import Glib.Windows.Client.Factory;

void ReadyDisplay() noexcept;

gl::framework::InitError
gl::Framework::Initialize(const gl::framework::Descriptor& setup)
{
	ReadyDisplay();

	try
	{
		myInstance = win32::CreateWindowEx<L"ManagedWindow">(setup.title, setup.wx, setup.wy, setup.ww, setup.wh);
	}
	catch (const std::exception& e)
	{
		std::printf("Exception: '%s'", e.what());
		return framework::InitError::FailedOnCreatingWindow;
	}

	gl::system::Descriptor gl_descriptor{};
	gl_descriptor.viewCh = setup.ww;
	gl_descriptor.viewCv = setup.wh;

	framework::InitError ok{};

	gl::CreateSystem(myInstance->AcquireContext(), std::move(gl_descriptor)).if_then<unsigned long>(
		[&](unsigned long&& code) noexcept {
		std::printf("Pixel Formatting Error: %lu\n", code);
		ok = framework::InitError::FailedOnSettingPixelFormat;
	}).if_then<opengl_system_t>(
		[&](opengl_system_t&& context) noexcept {
		glSystem = std::move(context);
		ok = framework::InitError::Success;
	});

	if (ok == framework::InitError::Success)
	{
		myInstance->SetPowerSave(setup.isPowersave);
	}

	return ok;
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
	SetRenderer(DefaultRenderer);

	using enum win32::managed_window::AwakeResult;
	const auto awakenening = myInstance->Awake();

	if (awakenening != Success)
	{
		//util::Println("Failed on awakening. (code: {}).", static_cast<int>(awakenening));

		std::rethrow_exception(myInstance->GetException());
		return;
	}

	myInstance->Start();
}

void
gl::Framework::AddEventHandler(gl::EventID id, const event_handler_t& procedure)
noexcept
{
	myInstance->AddEventHandler(id, procedure);
}

void
gl::Framework::AddEventHandler(gl::EventID id, event_handler_t&& procedure)
noexcept
{
	myInstance->AddEventHandler(id, std::move(procedure));
}

void
gl::Framework::RemoveEventHandler(gl::EventID id)
noexcept
{
	myInstance->RemoveEventHandler(id);
}

void
gl::Framework::SetRenderer(render_t handler)
noexcept
{
	myInstance->SetRenderer(
		[this, localRenderer = std::move(handler)](
		ManagedWindow& window,
		GraphicDeviceContext& ctx) {

		glSystem->Begin(ctx);
		localRenderer();
		glSystem->End();
	});
}

void
gl::Framework::DefaultRenderer()
noexcept
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.1f, 0.2f, 0.3f);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
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
