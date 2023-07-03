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
gl::device::MakePatternBrush(const native::RawBitmap& pattern_img)
noexcept
{
	return ColorBrush{ ::CreatePatternBrush(pattern_img) };
}
