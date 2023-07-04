module;
#include "Internal.hpp"
module Glib.Device.Resource.IBitmap;

gl::device::resource::IBitmap
gl::device::resource::IBitmap::Copy()
const noexcept
{
	auto& handle = GetHandle();
	if (handle)
	{
	}

	return IBitmap();
}

bool
gl::device::resource::IBitmap::TryCopy(IBitmap& output)
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

	return false;
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
gl::device::resource::IBitmap::Draw(const ISurface& context, const int& x, const int& y)
const noexcept
{
	return false;
}

bool
gl::device::resource::IBitmap::GetPixel(const ISurface& context, const int& x, const int& y, Colour& output)
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
