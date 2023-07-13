module;
#include "ImageLoader.inl"

module Glib.Windows.Resource.Bitmap;
import <type_traits>;
import Utility.Monad;
import Glib.Windows.Colour;
import Glib.Windows.IWindow;
import Glib.Windows.Context;
import Glib.Windows.CompatibleContext;
import Glib.Windows.Resource.CompatibleBitmap;

util::Monad<gl::win32::resource::Bitmap>
gl::win32::resource::Bitmap::Load(const FilePath& path)
noexcept
{
	if (auto result = ::_LoadBitmap(path); result.has_value<HBITMAP>())
	{
		return Bitmap{ result.get<HBITMAP>() };
	}
	else
	{
		::wprintf_s(L"Failed to load a bitmap from the file: %s\nError: %d\n", path.c_str(), result.get<unsigned long>());
		return util::nullopt;
	}
}

bool
gl::win32::resource::Bitmap::TryLoad(const FilePath& path, Bitmap& output)
noexcept
{
	if (auto result = Load(path); result.has_value())
	{
		output = Bitmap{ std::move(result).value() };
		return true;
	}
	else
	{
		return false;
	}
}

util::Monad<gl::win32::resource::Bitmap>
gl::win32::resource::Bitmap::Load(const int& id)
noexcept
{
	auto result = ::_LoadResourceBitmap(MAKEINTRESOURCE(id));
	if (result.has_value<HBITMAP>())
	{
		return Bitmap{ result.get<HBITMAP>() };
	}
	else
	{
		::wprintf_s(L"Failed to load a bitmap from the resource: %d\nError: %d\n", id, result.get<unsigned long>());
		return util::nullopt;
	}
}

bool
gl::win32::resource::Bitmap::TryLoad(const int& id, Bitmap& output)
noexcept
{
	if (auto result = Load(id); result.has_value())
	{
		output = Bitmap{ std::move(result).value() };
		return true;
	}
	else
	{
		return false;
	}
}

gl::win32::resource::Bitmap
gl::win32::resource::Bitmap::Copy(const IContext& context)
const noexcept
{
	Bitmap result{};
	TryCopy(context, result);
	return result;
}

bool
gl::win32::resource::Bitmap::TryCopy(const IContext& context, Bitmap& output)
const noexcept
{
	const native::RawBitmap& handle = GetHandle();
	if (nullptr == handle)
	{
		return false;
	}

	if (0 == cachedWidth || 0 == cachedHeight)
	{
		return false;
	}

	CompatibleContext current = context.CreateCompatibleContext();
	if (nullptr == current)
	{
		return false;
	}

	CompatibleBitmap bitmap = current.CreateCompatibleBitmap(cachedWidth, cachedHeight);
	if (nullptr == bitmap)
	{
		return false;
	}

	auto previous = current.Select(bitmap);

	bool result = (0 == ::BitBlt(current
		, 0, 0, cachedWidth, cachedHeight
		, context, 0, 0
		, SRCCOPY));

	current.Select(previous);

	output = Bitmap(std::move(bitmap));

	return result;
}

bool
gl::win32::resource::Bitmap::Fill(const Colour& color)
noexcept
{
	GlobalDeviceContext render_context = GlobalDeviceContext();
	if (nullptr == render_context)
	{
		return false;
	}

	CompatibleContext current = render_context.CreateCompatibleContext();
	if (nullptr == current)
	{
		return false;
	}


	return false;
}

void
gl::win32::resource::Bitmap::Mirror()
noexcept
{}

void
gl::win32::resource::Bitmap::Flip()
noexcept
{}

void
gl::win32::resource::Bitmap::Rotate(float angle)
noexcept
{}

void
gl::win32::resource::Bitmap::RotateR(float angle)
noexcept
{}

void
gl::win32::resource::Bitmap::RotateL(float angle)
noexcept
{}

bool
gl::win32::resource::Bitmap::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		const bool result = 0 != Delegate(::DeleteObject);
		base::operator=(nullifier);

		return result;
	}

	return false;
}

bool
gl::win32::resource::Bitmap::Draw(const IWindow& window_handle, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	GlobalDeviceContext render_context = GlobalDeviceContext();
	if (nullptr == render_context)
	{
		return false;
	}

	DeviceContext window_context = window_handle.AcquireContext();
	if (nullptr == window_context)
	{
		return false;
	}

	return Draw(render_context, window_context, x, y, srcx, srcy);
}

bool
gl::win32::resource::Bitmap::Draw(const IContext& render_context, IContext& window_context, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	auto previous = window_context.Select(*this);

	const bool result = (0 == ::BitBlt(window_context
		, x, y, cachedWidth, cachedHeight
		, render_context
		, srcx, srcy, SRCCOPY));

	window_context.Select(previous);

	return result;
}

bool
gl::win32::resource::Bitmap::GetPixel(const IContext& context, const int& x, const int& y, Colour& output)
const noexcept
{
	if (RawRGB result = context.Delegate(::GetPixel, x, y); CLR_INVALID != result)
	{
		output = MakeColor(result);

		return true;
	}
	else
	{
		return false;
	}
}

int
gl::win32::resource::Bitmap::GetWidth()
const noexcept
{
	return cachedWidth;
}

int
gl::win32::resource::Bitmap::GetHeight()
const noexcept
{
	return cachedHeight;
}

gl::win32::resource::Bitmap::Bitmap(const handle_type& handle)
noexcept
	: base(handle)
	, shouldDestroy(nullptr != handle)
{
	if (nullptr == handle)
	{
		return;
	}

	::BITMAP result{};

	if (0 != ::GetObject(handle, sizeof(::BITMAP), &result))
	{
		cachedWidth = result.bmWidth;
		cachedHeight = result.bmHeight;
	}
}

gl::win32::resource::Bitmap::Bitmap(handle_type&& handle)
noexcept
	: base(std::move(handle))
	, shouldDestroy(nullptr != handle)
{
	if (nullptr == handle)
	{
		return;
	}

	::BITMAP result{};

	if (0 != ::GetObject(GetHandle(), sizeof(::BITMAP), &result))
	{
		cachedWidth = result.bmWidth;
		cachedHeight = result.bmHeight;
	}
}

gl::win32::resource::Bitmap::~Bitmap()
noexcept
{
	if (shouldDestroy)
	{
		Destroy();
	}
}
