module;
#include "Internal.hpp"

module Glib.Device.Resource.Pen;
import <type_traits>;

gl::win32::resource::Pen::Pen(const gl::win32::resource::PenStyles& style, const int& width, const  gl::win32::Colour& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color.ToRaw()))
	, myStyle(style), myColor(color), mySize(width)
{}

gl::win32::resource::Pen::Pen(const PenStyles& style, const int& width, Colour&& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color.ToRaw()))
	, myStyle(style), myColor(std::move(color)), mySize(width)
{}

gl::win32::resource::Pen::Pen(const PenStyles& style, const int& width, const RawRGB& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color))
	, myStyle(style), myColor(MakeColor(color)), mySize(width)
{}

gl::win32::resource::Pen::Pen(const PenStyles& style, const int& width, RawRGB&& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color))
	, myStyle(style), myColor(MakeColor(std::move(color))), mySize(width)
{}

gl::win32::resource::Pen::~Pen()
noexcept
{
	Destroy();
}

void
gl::win32::resource::Pen::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		Delegate(::DeleteObject);
		base::operator=(nullptr);
	}
}

const gl::win32::resource::PenStyles&
gl::win32::resource::Pen::GetStyle()
const& noexcept
{
	return myStyle;
}

gl::win32::resource::PenStyles&&
gl::win32::resource::Pen::GetStyle()
&& noexcept
{
	return std::move(myStyle);
}

const int&
gl::win32::resource::Pen::GetSize()
const& noexcept
{
	return mySize;
}

int&& gl::win32::resource::Pen::GetSize()
&& noexcept
{
	return std::move(mySize);
}

gl::win32::Colour&
gl::win32::resource::Pen::GetColor()
& noexcept
{
	return myColor;
}

const gl::win32::Colour&
gl::win32::resource::Pen::GetColor()
const& noexcept
{
	return myColor;
}

gl::win32::Colour&&
gl::win32::resource::Pen::GetColor()
&& noexcept
{
	return std::move(myColor);
}

const gl::win32::Colour&&
gl::win32::resource::Pen::GetColor()
const&& noexcept
{
	return std::move(myColor);
}

gl::win32::resource::Pen&
gl::win32::resource::Pen::operator=(nullptr_t)
noexcept
{
	Destroy();
	return *this;
}
