module;
#include "Internal.hpp"

module Glib.Device.Brush.Component;
import <type_traits>;

namespace gl::device
{
	constexpr int make_index(const ColoredComponent& target) noexcept
	{
		return static_cast<int>(target);
	}

	native::NativeColorBrush acquire_brush(ColoredComponent target) noexcept
	{
		return ::GetSysColorBrush(make_index(target));
	}

	native::NativeColorBrush acquire_brush(int target) noexcept
	{
		return ::GetSysColorBrush(target);
	}

	static constexpr int cachedBrushSize = make_index(ColoredComponent::Hyperlink) + 1;
	static native::NativeColorBrush cachedBrushes[cachedBrushSize];
}

const gl::device::native::NativeColorBrush&
gl::device::GetComponentColouring(gl::device::ColoredComponent target)
noexcept
{
	native::NativeColorBrush& stock = cachedBrushes[make_index(target)];
	if (stock == nullptr)
	{
		stock = acquire_brush(target);
	}

	return stock;
}

const gl::device::native::NativeColorBrush&
gl::device::MakeDefaultComponentColouring()
noexcept
{
	return GetComponentColouring<colored_components::Background>();
}
