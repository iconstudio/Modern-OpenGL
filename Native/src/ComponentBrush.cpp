module;
#include "Internal.hpp"

module Glib.Windows.Resource.Brush.Component;
import <type_traits>;

namespace gl::win32
{
	constexpr int make_index(const ColoredComponent& target) noexcept
	{
		return static_cast<int>(target);
	}

	native::RawColorBrush acquire_brush(ColoredComponent target) noexcept
	{
		return ::GetSysColorBrush(make_index(target));
	}

	native::RawColorBrush acquire_brush(int target) noexcept
	{
		return ::GetSysColorBrush(target);
	}

	static constexpr int cachedBrushSize = make_index(ColoredComponent::Hyperlink) + 1;
	static native::RawColorBrush cachedBrushes[cachedBrushSize];
}

const gl::win32::native::RawColorBrush&
gl::win32::GetComponentColouring(gl::win32::ColoredComponent target)
noexcept
{
	native::RawColorBrush& stock = cachedBrushes[make_index(target)];
	if (stock == nullptr)
	{
		stock = acquire_brush(target);
	}

	return stock;
}

const gl::win32::native::RawColorBrush&
gl::win32::MakeDefaultComponentColouring()
noexcept
{
	return GetComponentColouring<colored_components::Background>();
}
