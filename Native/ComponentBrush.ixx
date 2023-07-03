module;
#include "Internal.hpp"

export module Glib.Device.Brush.Component;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.Brush;

namespace gl::device
{
	export extern "C" enum class [[nodiscard]] ColoredComponent : int
	{
		Window = 5, // COLOR_WINDOW
		Text = 8, // COLOR_WINDOWTEXT
		Highlight = 13, // COLOR_HIGHLIGHT
		HighlightText = 14, // COLOR_HIGHLIGHTTEXT
		ButtonFace = 15, // COLOR_3DFACE
		GrayText = 17, // COLOR_GRAYTEXT
		BtnText = 18, // COLOR_BTNTEXT
		Hyperlink = 26, // COLOR_HOTLIGHT
	};

	export extern "C" namespace colored_components
	{
		inline constexpr ColoredComponent Text = ColoredComponent::Text;
		inline constexpr ColoredComponent Background = ColoredComponent::Window;
		inline constexpr ColoredComponent Window = ColoredComponent::Window;
		inline constexpr ColoredComponent ButtonText = ColoredComponent::BtnText;
		inline constexpr ColoredComponent ButtonFace = ColoredComponent::ButtonFace;

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

		constexpr InternalCColor(const native::NativeColorBrush& brush) noexcept
			: myBrush(brush)
		{}

		constexpr InternalCColor(native::NativeColorBrush&& brush) noexcept
			: myBrush(std::move(brush))
		{}

		native::NativeColorBrush myBrush;
	};

	const native::NativeColorBrush& GetComponentColouring(ColoredComponent) noexcept;

	export template<ColoredComponent Target>
		[[nodiscard]]
	const native::NativeColorBrush&
		GetComponentColouring()
		noexcept(COLOR_WINDOW <= static_cast<int>(Target) && static_cast<int>(Target) <= COLOR_HOTLIGHT)
	{
		static InternalCColor<Target> stock = ::GetSysColorBrush(static_cast<int>(Target));
		return stock.myBrush;
	}

	export
		[[nodiscard]]
	const native::NativeColorBrush&
		MakeDefaultComponentColouring() noexcept
	{
		return GetComponentColouring<colored_components::Background>();
	}
}
