module;
#include "Internal.hpp"

module Glib.Device.Pen;
import <type_traits>;

gl::device::Pen::Pen(const gl::device::PenStyles& style, const int& width, const  gl::device::Colour& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color.ToRaw()))
	, myStyle(style), myColor(color), mySize(width)
{}

gl::device::Pen::Pen(const PenStyles& style, const int& width, Colour&& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color.ToRaw()))
	, myStyle(style), myColor(std::move(color)), mySize(width)
{}

gl::device::Pen::Pen(const PenStyles& style, const int& width, const RawRGB& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color))
	, myStyle(style), myColor(device::MakeColor(color)), mySize(width)
{}

gl::device::Pen::Pen(const PenStyles& style, const int& width, RawRGB&& color)
noexcept
	: base(::CreatePen(static_cast<int>(style), width, color))
	, myStyle(style), myColor(device::MakeColor(std::move(color))), mySize(width)
{}

gl::device::Pen::~Pen()
noexcept
{
	Destroy();
}

void
gl::device::Pen::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		Delegate(::DeleteObject);
		base::operator=(nullptr);
	}
}

gl::device::Pen&
gl::device::Pen::operator=(nullptr_t)
noexcept
{
	Destroy();
	return *this;
}
