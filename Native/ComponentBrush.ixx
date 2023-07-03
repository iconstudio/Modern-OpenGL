module;
#include "Internal.hpp"

export module Glib.Device.Brush.Component;
import <type_traits>;
export import Glib.Device.Brush;

namespace gl::device
{
	export extern "C" enum class [[nodiscard]] ColoredComponent : int
	{
		Window = COLOR_WINDOW,
		Text = COLOR_WINDOWTEXT,
		GrayText = COLOR_GRAYTEXT,
		BtnText = COLOR_BTNTEXT,
		Highlight = COLOR_HIGHLIGHT,
		HighlightText = COLOR_HIGHLIGHTTEXT,
		Face3D = COLOR_3DFACE,
		Hyperlink = COLOR_HOTLIGHT,
	};

	export extern "C" namespace colored_components
	{
		inline constexpr ColoredComponent Text = ColoredComponent::Text;
		inline constexpr ColoredComponent Background = ColoredComponent::Window;
		inline constexpr ColoredComponent Window = ColoredComponent::Window;
		inline constexpr ColoredComponent ButtonText = ColoredComponent::BtnText;
		inline constexpr ColoredComponent ButtonFace = ColoredComponent::Face3D;

		inline constexpr ColoredComponent HighlightText = ColoredComponent::HighlightText;
		inline constexpr ColoredComponent HighlightBackground = ColoredComponent::Highlight;
		inline constexpr ColoredComponent GrayText = ColoredComponent::GrayText;
		inline constexpr ColoredComponent Hyperlink = ColoredComponent::Hyperlink;
	}

	template<ColoredComponent Target>
	struct InternalCColor
	{
		constexpr InternalCColor() noexcept = default;
		constexpr ~InternalCColor() noexcept = default;

		constexpr InternalCColor(const NativeColorBrush& brush) noexcept
			: myBrush(brush)
		{}

		constexpr InternalCColor(NativeColorBrush&& brush) noexcept
			: myBrush(std::move(brush))
		{}

		NativeColorBrush myBrush;
	};

	export template<ColoredComponent Target>
		[[nodiscard]]
	const NativeColorBrush&
		GetComponentColouring()
		noexcept(COLOR_WINDOW <= static_cast<int>(Target) && static_cast<int>(Target) <= COLOR_HOTLIGHT)
	{
		static InternalCColor<Target> stock = ::GetSysColorBrush(static_cast<int>(Target));
		return stock.myBrush;
	}

	export
		[[nodiscard]]
	const NativeColorBrush&
		MakeDefaultComponentColouring() noexcept
	{
		return GetComponentColouring<colored_components::Background>();
	}
}
