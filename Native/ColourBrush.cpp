module;
#include "Internal.hpp"
module Glib.Device.Resource.Brush;

gl::device::resource::ColorBrush::~ColorBrush()
noexcept
{
	Destroy();
}

bool
gl::device::resource::ColorBrush::Destroy()
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

gl::device::resource::ColorBrush&
gl::device::resource::ColorBrush::operator=(nullptr_t)
noexcept
{
	base::operator=(nullptr);
	return *this;
}

gl::device::resource::ColorBrush&
gl::device::resource::ColorBrush::operator=(handle_type&& brush)
noexcept
{
	base::operator=(std::move(brush));
	return *this;
}

gl::device::resource::ColorBrush&
gl::device::resource::ColorBrush::operator=(ColorBrush&& other) noexcept
{
	base::operator=(std::move(other));
	return *this;
}

gl::device::resource::ColorBrush
gl::device::MakeColorBrush(const unsigned long& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(color) };
}

gl::device::resource::ColorBrush
gl::device::MakeColorBrush(unsigned long&& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(std::move(color)) };
}

gl::device::resource::ColorBrush
gl::device::MakeColorBrush(const Colour& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(color.ToRaw()) };
}

gl::device::resource::ColorBrush
gl::device::MakeColorBrush(Colour&& color)
noexcept
{
	return ColorBrush{ ::CreateSolidBrush(std::move(color).ToRaw()) };
}

gl::device::resource::ColorBrush
gl::device::MakePatternBrush(const BrushPatterns& pattern, const unsigned long& rgb)
noexcept
{
	return ColorBrush{ ::CreateHatchBrush(static_cast<int>(pattern), rgb) };
}

gl::device::resource::ColorBrush
gl::device::MakePatternBrush(const BrushPatterns& pattern, const Colour& argb)
noexcept
{
	return ColorBrush{ ::CreateHatchBrush(static_cast<int>(pattern), argb.ToRaw()) };
}

gl::device::resource::ColorBrush
gl::device::MakeStampBrush(const native::RawBitmap& image)
noexcept
{
	return ColorBrush{ ::CreatePatternBrush(image) };
}
