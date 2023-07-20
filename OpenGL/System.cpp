module;
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

module Glib;
import <memory>;
import <cstdio>;
import Utility.Monad.Loosen;
import Glib.Windows.Context.Renderer;
import :System;
import :Utility;
import Glib.Blender;
import Glib.Culling;

static inline constexpr ::PIXELFORMATDESCRIPTOR opengl_format =
{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,                     // version number
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_COMPOSITION | PFD_SWAP_EXCHANGE | PFD_GENERIC_ACCELERATED,
	PFD_TYPE_RGBA,         // RGBA type
	32,
	0, 0, 0, 0, 0, 0,      // color bits ignored
	8,
	0,                     // shift bit ignored
	0,                     // no accumulation buffer
	0, 0, 0, 0,            // accum bits ignored
	16,
	8,
	0,                     // no auxiliary buffer
	PFD_MAIN_PLANE,        // main layer
	0,                     // reserved
	0, 0, 0                // layer masks ignored
};

gl::System::System()
noexcept
	: base1(nullptr), base2()
{}

unsigned long
_InitializePixelFormat(const gl::win32::IContext& hdc, PIXELFORMATDESCRIPTOR& my_format, int& my_target)
noexcept;

unsigned long
gl::System::Initialize(const gl::win32::IContext& hdc, const gl::system::Descriptor& descriptor)
noexcept
{
	mySettings = descriptor;

	::PIXELFORMATDESCRIPTOR my_format = opengl_format;
	int my_target = 0;

	if (mySettings.doubleBuffered)
	{
		my_format.dwFlags |= PFD_DOUBLEBUFFER;
	}

	if (unsigned long error = _InitializePixelFormat(hdc, my_format, my_target); 0 != error)
	{
		return error;
	}

	base1::operator=(hdc.Delegate(::wglCreateContext));
	if (nullptr == *this)
	{
		unsigned long error = ::GetLastError();
		std::printf("Failed on creating a opengl context. (code: %u)\n", error);
		return error;
	}

	if (0 != (my_format.dwFlags & PFD_DOUBLEBUFFER))
	{
		myPainter = gl::DoublePainter;
	}
	else
	{
		myPainter = gl::SinglePainter;
	}

	return _InitializeSystem();
}

bool gl::System::Begin(win32::GraphicDeviceContext& painter) noexcept
{
	if (0 == painter.Delegate(::wglMakeCurrent, GetHandle()))
	{
		std::printf("Failed to begin rendering. (gl error code: %u)\n", ::glGetError());

		return false;
	}

	nativeContext = std::addressof(painter);

	myBlender->Apply();
	::glViewport(viewPort.x, viewPort.y, viewPort.w, viewPort.h);
	::glClear(GL_DEPTH_BUFFER_BIT);

	::glMatrixMode(GL_PROJECTION);
	::glPushMatrix();
	::glLoadIdentity();

	global::SetBackgroundColour(mySettings.borderColour);
	::glClear(GL_COLOR_BUFFER_BIT);

	::glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	global::SetBackgroundColour(mySettings.backgroundColour);

	::glMatrixMode(GL_MODELVIEW);
	::glPushMatrix();
	::glLoadIdentity();

	return true;
}

bool gl::System::End() noexcept
{
	::glPopMatrix();

	::glMatrixMode(GL_PROJECTION);
	::glPopMatrix();

	myPainter(nativeContext);

	return 0 != ::wglMakeCurrent(nullptr, nullptr);
}

unsigned long
gl::System::_InitializeSystem()
noexcept
{
	if (mySettings.alphaBlend)
	{
		myBlender = new gl::Blender{ gl::DefaultAlpha };
	}

	if (mySettings.hiddenSurfaceRemoval)
	{
		global::SetState(gl::State::Culling);
		gl::Culling(gl::Face::Back);
		gl::CullingDirection(mySettings.cullingIsClockwise);
	}

	global::SetState(gl::State::Depth);

	aspectRatio = static_cast<double>(mySettings.viewCh) / static_cast<double>(mySettings.viewCv);

	if (mySettings.vSync)
	{
		typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		const char* extensions = (char*)glGetString(GL_EXTENSIONS);

		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

		// no glew, so use old way
		if (wglSwapIntervalEXT)
		{
			wglSwapIntervalEXT(1);
		}
		//::wglSwapIntervalEXT(1);
	}

	return 0;
}

gl::System::~System()
noexcept
{
	if (nullptr != GetHandle())
	{
		Delegate(::wglDeleteContext);
	}

	delete myBlender;
}

gl::SystemCreation
gl::CreateSystem(const win32::IContext& hdc, const gl::system::Descriptor& setup)
noexcept
{
	auto result = std::make_shared<gl::System>();

	if (0 != result->Initialize(hdc, setup))
	{
		return ::GetLastError();
	}

	return result;
}

gl::SystemCreation
gl::CreateSystem(const win32::IContext& hdc, gl::system::Descriptor&& setup)
noexcept
{
	auto result = std::make_shared<gl::System>();

	if (0 != result->Initialize(hdc, std::move(setup)))
	{
		return ::GetLastError();
	}

	return result;
}

unsigned long
_InitializePixelFormat(const gl::win32::IContext& hdc, PIXELFORMATDESCRIPTOR& my_format, int& my_target)
noexcept
{
	const int target = ::ChoosePixelFormat(hdc, &my_format);
	if (0 == target)
	{
		unsigned long error = ::GetLastError();
		std::printf("Failed on acquiring a pixel format. (code: %u)\n", error);
		return error;
	}

	const int check = ::DescribePixelFormat(hdc, target, sizeof(my_format), &my_format);
	if (0 == check)
	{
		unsigned long error = ::GetLastError();
		std::printf("Failed on reading a pixel format %d. (code: %u)\n", target, error);
		return error;
	}

	if (0 == ::SetPixelFormat(hdc, target, &my_format))
	{
		unsigned long error = ::GetLastError();
		std::printf("Failed on setting pixel format %d. (code: %u)\n", target, error);
		return error;
	}

	if (0 == (my_format.dwFlags & PFD_SUPPORT_OPENGL))
	{
		unsigned long error = ::GetLastError();
		std::printf("Failed on checking a pixel format %d. (code: %u)\n", target, error);
		return error;
	}

	my_target = target;

	return 0UL;
}

void
gl::SinglePainter(gl::win32::GraphicDeviceContext* const&)
noexcept
{
	::glFlush();
}

void
gl::DoublePainter(gl::win32::GraphicDeviceContext* const& context)
noexcept
{
	context->Delegate(::SwapBuffers);
}

void
gl::System::KeepAspectRatio(bool keep_ratio)
noexcept
{
	keepAspectRatio = keep_ratio;
	if (keep_ratio)
	{
		//gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
	}
	else
	{
		//gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
	}

}

void gl::System::SetViewPosition(int x, int y) noexcept
{
	viewPort.x = x;
	viewPort.y = y;
}

void
gl::System::SetViewSize(int width, int height)
noexcept
{
	viewPort.w = width;
	viewPort.h = height;
}

void
gl::System::SetViewPort(const gl::Rect& size)
noexcept
{
	viewPort = size;
}

void
gl::System::SetViewPort(gl::Rect&& size)
noexcept
{
	viewPort = std::move(size);
}

void
gl::System::SetViewPort(int x, int y, int width, int height)
noexcept
{
	SetViewPort(gl::Rect{ x, y, width, height });
}

const gl::Rect&
gl::System::GetViewPort()
const noexcept
{
	return viewPort;
}

void
gl::System::UpdateViewPort(int client_width, int client_height)
noexcept
{
	if (keepAspectRatio)
	{
		if (client_height < client_width)
		{
			const int new_width = static_cast<int>(static_cast<double>(client_height) * aspectRatio);
			const int new_x = (client_width - new_width) / 2;
			SetViewPort(new_x, 0, new_width, client_height);
		}
		else
		{
			const int new_height = static_cast<int>(static_cast<double>(client_width) / aspectRatio);
			const int new_y = (client_height - new_height) / 2;
			SetViewPort(0, new_y, client_width, new_height);
		}
	}
	else
	{
		SetViewPort(0, 0, client_width, client_height);
	}
}

double
gl::System::GetAspectRatio()
const noexcept
{
	return aspectRatio;
}
