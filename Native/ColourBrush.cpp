module;
#include "Internal.hpp"

module Glib.Device.Brush;

gl::device::ColorBrush::~ColorBrush()
noexcept
{
	Destroy();
}

void
gl::device::ColorBrush::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		Delegate(::DeleteObject);
		base::operator=(nullptr);
	}
}

gl::device::ColorBrush&
gl::device::ColorBrush::operator=(nullptr_t)
noexcept
{
	Destroy();

	return *this;
}

gl::device::ColorBrush
gl::device::MakeColorBrush(const unsigned long& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(color) };
}

gl::device::ColorBrush
gl::device::MakeColorBrush(unsigned long&& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(std::move(color)) };
}

gl::device::ColorBrush
gl::device::MakeColorBrush(const Colour& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(color.ToRaw()) };
}

gl::device::ColorBrush
gl::device::MakeColorBrush(Colour&& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(std::move(color).ToRaw()) };
}

gl::device::ColorBrush
gl::device::MakePatternBrush(const BrushPatterns& pattern, const unsigned long& rgb)
noexcept
{
	return ColorBrush{ ::CreateHatchBrush(static_cast<int>(pattern), rgb) };
}

gl::device::ColorBrush
gl::device::MakePatternBrush(const BrushPatterns& pattern, const Colour& argb)
noexcept
{
	return ColorBrush{ ::CreateHatchBrush(static_cast<int>(pattern), argb.ToRaw()) };
}

gl::device::ColorBrush
gl::device::MakeStampBrush(const native::RawBitmap& image)
noexcept
{
	return ColorBrush{ ::CreatePatternBrush(image) };
}
