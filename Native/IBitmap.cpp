module;
#include "Internal.hpp"
module Glib.Device.Resource.IBitmap;

gl::device::resource::IBitmap
gl::device::resource::IBitmap::Copy(const IContext& context)
const noexcept
{
	IBitmap result{};
	TryCopy(context, result);
	return result;
}

bool
gl::device::resource::IBitmap::TryCopy(const IContext& context, IBitmap& output)
const noexcept
{
	auto& handle = GetHandle();
	if (nullptr == handle)
	{
		return false;
	}

	if (0 == cachedWidth || 0 == cachedHeight)
	{
		return false;
	}

	const HDC& hdc = context.GetHandle();
	if (nullptr == hdc)
	{
		return false;
	}

	HDC memory = context.Delegate(::CreateCompatibleDC);
	if (nullptr == memory)
	{
		return false;
	}

	HBITMAP bitmap = ::CreateCompatibleBitmap(hdc, cachedWidth, cachedHeight);
	if (nullptr == bitmap)
	{
		::DeleteDC(memory);

		return false;
	}

	HGDIOBJ previous = ::SelectObject(memory, bitmap);
	if (nullptr == previous)
	{
		::DeleteObject(bitmap);
		::DeleteDC(memory);

		return false;
	}

	if (0 == ::BitBlt(memory, 0, 0, cachedWidth, cachedHeight, hdc, 0, 0, SRCCOPY))
	{
		::SelectObject(memory, previous);
		::DeleteObject(bitmap);
		::DeleteDC(memory);

		return false;
	}

	::SelectObject(memory, previous);

	output = IBitmap(bitmap);

	::DeleteDC(memory);
	return true;
}

bool
gl::device::resource::IBitmap::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		bool result = 0 != Delegate(::DeleteObject);
		base::operator=(nullifier);

		return result;
	}

	return false;
}

bool
gl::device::resource::IBitmap::Draw(const IWindowHandle& window_handle, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	IContext render_context = IWindowHandle{}.AcquireNativeContext();
	if (nullptr == render_context)
	{
		return false;
	}

	IContext window_context = window_handle.AcquireNativeContext();
	if (nullptr == window_context)
	{
		return false;
	}

	bool result = Draw(render_context, window_context, x, y, srcx, srcy);

	window_handle.ReleaseNativeContext(window_context);
	IWindowHandle{}.ReleaseNativeContext(render_context);

	return result;
}

bool
gl::device::resource::IBitmap::Draw(const IContext& render_context, IContext& window_context, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	HGDIOBJ previous = window_context.Delegate(::SelectObject, GetHandle());

	bool result = (0 == ::BitBlt(window_context
		, x, y, cachedWidth, cachedHeight
		, render_context
		, srcx, srcy, SRCCOPY));

	window_context.Delegate(::SelectObject, previous);

	return result;
}

bool
gl::device::resource::IBitmap::GetPixel(const IContext& context, const int& x, const int& y, Colour& output)
const
{
	if (RawRGB result = context.Delegate(::GetPixel, x, y); CLR_INVALID != result)
	{
		output = device::MakeColor(result);

		return true;
	}
	else
	{
		return false;
	}
}

int
gl::device::resource::IBitmap::GetWidth()
const noexcept
{
	return cachedWidth;
}

int
gl::device::resource::IBitmap::GetHeight()
const noexcept
{
	return cachedHeight;
}

gl::device::resource::IBitmap::IBitmap(const handle_type& handle)
noexcept
	: base(handle)
{
	::SIZE result{};
	if (0 != ::GetBitmapDimensionEx(handle, &result))
	{
		cachedWidth = result.cx;
		cachedHeight = result.cy;
	}
}

gl::device::resource::IBitmap::IBitmap(handle_type&& handle)
noexcept
	: base(std::move(handle))
	, shouldDestroy(true)
{
	::SIZE result{};
	if (0 != ::GetBitmapDimensionEx(GetHandle(), &result))
	{
		cachedWidth = result.cx;
		cachedHeight = result.cy;
	}
}

gl::device::resource::IBitmap::~IBitmap()
noexcept
{
	if (shouldDestroy)
	{
		Destroy();
	}
}
