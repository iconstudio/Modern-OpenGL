module;
#include "Internal.hpp"

module Glib.Device.Brush.Component;
import <type_traits>;

template<gl::device::ColoredComponent Target>
struct InternalCColor
{
	constexpr InternalCColor() noexcept = default;
	constexpr ~InternalCColor() noexcept = default;

	constexpr InternalCColor(const gl::device::native::NativeColorBrush& brush) noexcept
		: myBrush(brush)
	{}

	constexpr InternalCColor(gl::device::native::NativeColorBrush&& brush) noexcept
		: myBrush(std::move(brush))
	{}

	gl::device::native::NativeColorBrush myBrush;
};

const gl::device::native::NativeColorBrush&
gl::device::GetComponentColouring(gl::device::ColoredComponent target)
noexcept
{
	static InternalCColor<Target> stock = ::GetSysColorBrush(static_cast<int>(Target));
	return stock.myBrush;
}

const gl::device::native::NativeColorBrush&
gl::device::MakeDefaultComponentColouring()
noexcept
{
	return GetComponentColouring<colored_components::Background>();
}
