module;
#include "Internal.hpp"
module Glib.Device.IContext;
import Glib.Device.CompatibleContext;
import Glib.Device.Resource.Brush;
import Glib.Device.Resource.Pen;
import Glib.Device.Resource.Palette;
import Glib.Device.Resource.Bitmap;
import Glib.Device.Resource.CompatibleBitmap;

gl::win32::IContext::~IContext() noexcept
{
	if (shouldDestroy && nullptr != GetHandle())
	{
		Destroy();
	}
}

gl::win32::CompatibleContext
gl::win32::IContext::CreateCompatibleContext()
const noexcept
{
	return Delegate(::CreateCompatibleDC);
}

gl::win32::resource::CompatibleBitmap
gl::win32::IContext::CreateCompatibleBitmap(const int& width, const int& height)
const noexcept
{
	return Delegate(::CreateCompatibleBitmap, width, height);
}

bool
gl::win32::IContext::Destroy()
noexcept
{
	return 0 != Delegate(::DeleteDC);
}

bool
gl::win32::IContext::Release()
noexcept
{
	return 0 != ::ReleaseDC(nullptr, GetHandle());
}

bool
gl::win32::IContext::Release(const gl::win32::native::HWND& owner)
noexcept
{
	return 0 != ::ReleaseDC(owner, GetHandle());
}

gl::win32::IContext::GraphicState
gl::win32::IContext::Select(const resource::ColorBrush& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

gl::win32::IContext::GraphicState
gl::win32::IContext::Select(const resource::Pen& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

gl::win32::IContext::GraphicState
gl::win32::IContext::Select(const resource::Palette& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

gl::win32::IContext::GraphicState
gl::win32::IContext::Select(const resource::Bitmap& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

void
gl::win32::IContext::Select(GraphicState& previous)
const noexcept
{
	Delegate(::SelectObject, previous.object);
}
