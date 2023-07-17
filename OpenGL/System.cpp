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

gl::System::~System()
noexcept
{
	if (nullptr != GetHandle())
	{
		Delegate(::wglDeleteContext);
	}
}

unsigned long
_InitializeSystem(const gl::win32::IContext& hdc, PIXELFORMATDESCRIPTOR& my_format, int& my_target)
noexcept;

unsigned long
gl::System::Initialize(const gl::win32::IContext& hdc, const gl::system::Descriptor& descriptor)
noexcept
{
	::PIXELFORMATDESCRIPTOR my_format = opengl_format;
	int my_target = 0;

	if (descriptor.doubleBuffered)
	{
		my_format.dwFlags |= PFD_DOUBLEBUFFER;
	}

	if (unsigned long error = _InitializeSystem(hdc, my_format, my_target); 0 != error)
	{
		return error;
	}

	if (0 == (my_format.dwFlags & PFD_SUPPORT_OPENGL))
	{
		unsigned long error = ::GetLastError();
		std::printf("Failed on checking a pixel format %d. (code: %u)\n", my_target, error);
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

	if (descriptor.alphaBlend)
	{
		global::SetState(gl::State::Blending);
	}

	global::SetBackgroundColour(gl::System::DefaultColour);
	global::SetState(gl::State::Depth);
	global::SetState(gl::State::Culling);

	::glCullFace(GL_BACK);
	::glMatrixMode(GL_PROJECTION);
	::glViewport(0, 0, descriptor.viewCx, descriptor.viewCy);
	::glLoadIdentity();

	return 0;
}

bool gl::System::Begin(win32::GraphicDeviceContext& painter) noexcept
{
	if (0 == painter.Delegate(::wglMakeCurrent, GetHandle()))
	{
		std::printf("Failed on selecting a pixel format. (code: %u)\n", ::GetLastError());

		return false;
	}

	nativeContext = std::addressof(painter);

	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool gl::System::End() noexcept
{
	myPainter(nativeContext);

	//::wglMakeCurrent(nativeContext, nullptr);
	return 0 != ::wglMakeCurrent(nullptr, nullptr);
}

gl::SystemCreation
gl::CreateSystem(const win32::IContext& hdc, const gl::system::Descriptor& setup)
noexcept
{
	auto result = std::make_shared<gl::System>();

	if (0 != result->Initialize(hdc, setup)
	)
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

	if (0 != result->Initialize(hdc, std::move(setup))
	)
	{
		return ::GetLastError();
	}

	return result;
}

void
gl::System::SetAspectRatio(bool keep_ratio)
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

unsigned long
_InitializeSystem(const gl::win32::IContext& hdc, PIXELFORMATDESCRIPTOR& my_format, int& my_target)
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

const gl::win32::Colour gl::System::DefaultColour = gl::win32::colors::Black;
