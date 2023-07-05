module;
#include "Internal.hpp"
module Glib.Device.IContext;
import Glib.Device.CompatibleContext;
import Glib.Device.Resource.Brush;
import Glib.Device.Resource.Pen;
import Glib.Device.Resource.Palette;
import Glib.Device.Resource.Bitmap;
import Glib.Device.Resource.CompatibleBitmap;

gl::device::IContext::~IContext() noexcept
{
	if (shouldDestroy && nullptr != GetHandle())
	{
		Destroy();
	}
}

gl::device::CompatibleContext
gl::device::IContext::CreateCompatibleContext()
const noexcept
{
	return Delegate(::CreateCompatibleDC);
}

gl::device::resource::CompatibleBitmap
gl::device::IContext::CreateCompatibleBitmap(const int& width, const int& height)
const noexcept
{
	return Delegate(::CreateCompatibleBitmap, width, height);
}

bool
gl::device::IContext::Destroy()
noexcept
{
	return 0 != Delegate(::DeleteDC);
}

bool
gl::device::IContext::Release()
noexcept
{
	return 0 != ::ReleaseDC(nullptr, GetHandle());
}

bool
gl::device::IContext::Release(const gl::device::native::HWND& owner)
noexcept
{
	return 0 != ::ReleaseDC(owner, GetHandle());
}

gl::device::IContext::GraphicState
gl::device::IContext::Select(const resource::ColorBrush& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

gl::device::IContext::GraphicState
gl::device::IContext::Select(const resource::Pen& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

gl::device::IContext::GraphicState
gl::device::IContext::Select(const resource::Palette& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

gl::device::IContext::GraphicState
gl::device::IContext::Select(const resource::Bitmap& obj)
const noexcept
{
	return GraphicState{ Delegate(::SelectObject, obj.GetHandle()) };
}

void
gl::device::IContext::Select(GraphicState& previous)
const noexcept
{
	Delegate(::SelectObject, previous.object);
}
