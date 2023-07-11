module;
#include "Internal.hpp"

module Glib.Device.Context.Renderer;
import <cstdio>;

PIXELFORMATDESCRIPTOR pixel_format =
{
	.nSize = sizeof(PIXELFORMATDESCRIPTOR),
	.nVersion = 1,
	.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SUPPORT_COMPOSITION | PFD_SWAP_EXCHANGE | PFD_GENERIC_ACCELERATED,
	.iPixelType = PFD_TYPE_RGBA,
	.cColorBits = 24,
};

gl::device::GraphicDeviceContext::GraphicDeviceContext(const gl::device::native::HWND& handle)
noexcept
	: base(::BeginPaint(handle, &myStatus))
	, myWindowHandle(handle)
	, myContext()
{
	myContext = ::wglCreateContext(myHandle);
	if (nullptr != myContext)
	{
		if (0 == ::wglMakeCurrent(myHandle, myContext))
		{
			std::printf("Failed on selecting a pixel format. (code: %u)\n", ::GetLastError());
		}
	}
	else
	{
		const int current_format_id = GetPixelFormat(GetHandle());

		if (0 == DescribePixelFormat(GetHandle(), current_format_id, sizeof(pixel_format), &pixel_format))
		{
			std::printf("Failed on reading a pixel format %d. (code: %u)\n", current_format_id, ::GetLastError());
			return;
		}

		if (0 == (pixel_format.dwFlags & PFD_SUPPORT_OPENGL))
		{
			std::printf("Failed on checking a pixel format %d. (code: %u)\n", current_format_id, ::GetLastError());
			return;
		}
	}
}

gl::device::GraphicDeviceContext::~GraphicDeviceContext()
noexcept
{
	::EndPaint(myWindowHandle, &myStatus);

	if (myContext)
	{
		//::wglMakeCurrent(GetHandle(), nullptr);
		::wglMakeCurrent(nullptr, nullptr);

		::wglDeleteContext(myContext);
	}
}

const gl::device::native::NativeOGL&
gl::device::GraphicDeviceContext::GetContext()
const& noexcept
{
	return myContext;
}

gl::device::native::PaintStruct&
gl::device::GraphicDeviceContext::GetPaintStruct()
noexcept
{
	return myStatus;
}

const gl::device::native::PaintStruct&
gl::device::GraphicDeviceContext::GetPaintStruct()
const noexcept
{
	return myStatus;
}
