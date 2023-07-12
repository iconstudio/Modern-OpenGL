module;
#include <Windows.h>

module Glib.GraphicContext;
import <cstdio>;

PIXELFORMATDESCRIPTOR pixel_format =
{
	.nSize = sizeof(PIXELFORMATDESCRIPTOR),
	.nVersion = 1,
	.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SUPPORT_COMPOSITION | PFD_SWAP_EXCHANGE | PFD_GENERIC_ACCELERATED,
	.iPixelType = PFD_TYPE_RGBA,
	.cColorBits = 24,
};

gl::GLContext::GLContext()
noexcept
	: base(nullptr)
{}

gl::GLContext::~GLContext()
noexcept
{
	if (nullptr != GetHandle())
	{
		::wglDeleteContext(GetHandle());
	}
}

bool
gl::GLContext::Initialize(const gl::device::IContext& hdc)
noexcept
{
	return false;
}

bool gl::GLContext::Begin(device::GraphicDeviceContext& painter) noexcept
{
	myHandle = ::wglCreateContext(painter);
	if (nullptr != myHandle)
	{
		if (0 == ::wglMakeCurrent(painter, myHandle))
		{
			std::printf("Failed on selecting a pixel format. (code: %u)\n", ::GetLastError());

			return false;
		}
	}
	else
	{
		const int current_format_id = GetPixelFormat(GetHandle());

		if (0 == DescribePixelFormat(GetHandle(), current_format_id, sizeof(pixel_format), &pixel_format))
		{
			std::printf("Failed on reading a pixel format %d. (code: %u)\n", current_format_id, ::GetLastError());

			return false;
		}

		if (0 == (pixel_format.dwFlags & PFD_SUPPORT_OPENGL))
		{
			std::printf("Failed on checking a pixel format %d. (code: %u)\n", current_format_id, ::GetLastError());

			return false;
		}
	}

	return true;
}

bool gl::GLContext::End() noexcept
{
	//::wglMakeCurrent(GetHandle(), nullptr);
	return 0 != ::wglMakeCurrent(nullptr, nullptr);
}
