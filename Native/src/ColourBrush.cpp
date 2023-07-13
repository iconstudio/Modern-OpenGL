module;
#include "Internal.hpp"
module Glib.Windows.Resource.Brush;

gl::win32::resource::ColorBrush::~ColorBrush()
noexcept
{
	Destroy();
}

bool
gl::win32::resource::ColorBrush::Destroy()
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

gl::win32::resource::ColorBrush&
gl::win32::resource::ColorBrush::operator=(nullptr_t)
noexcept
{
	base::operator=(nullptr);
	return *this;
}

gl::win32::resource::ColorBrush&
gl::win32::resource::ColorBrush::operator=(handle_type&& brush)
noexcept
{
	base::operator=(std::move(brush));
	return *this;
}

gl::win32::resource::ColorBrush&
gl::win32::resource::ColorBrush::operator=(ColorBrush&& other) noexcept
{
	base::operator=(std::move(other));
	return *this;
}

gl::win32::resource::ColorBrush
gl::win32::MakeColorBrush(const unsigned long& color)
noexcept
{
	return resource::ColorBrush{ ::CreateSolidBrush(color) };
}

gl::win32::resource::ColorBrush
gl::win32::MakeColorBrush(unsigned long&& color)
noexcept
{
	return resource::ColorBrush{ ::CreateSolidBrush(std::move(color)) };
}

gl::win32::resource::ColorBrush
gl::win32::MakeColorBrush(const Colour& color)
noexcept
{
	return resource::ColorBrush{ ::CreateSolidBrush(color.ToRaw()) };
}

gl::win32::resource::ColorBrush
gl::win32::MakeColorBrush(Colour&& color)
noexcept
{
	return resource::ColorBrush{ ::CreateSolidBrush(std::move(color).ToRaw()) };
}

gl::win32::resource::ColorBrush
gl::win32::MakePatternBrush(const resource::BrushPatterns& pattern, const unsigned long& rgb)
noexcept
{
	return resource::ColorBrush{ ::CreateHatchBrush(static_cast<int>(pattern), rgb) };
}

gl::win32::resource::ColorBrush
gl::win32::MakePatternBrush(const resource::BrushPatterns& pattern, const Colour& argb)
noexcept
{
	return resource::ColorBrush{ ::CreateHatchBrush(static_cast<int>(pattern), argb.ToRaw()) };
}

gl::win32::resource::ColorBrush
gl::win32::MakeStampBrush(const native::RawBitmap& image)
noexcept
{
	return resource::ColorBrush{ ::CreatePatternBrush(image) };
}
