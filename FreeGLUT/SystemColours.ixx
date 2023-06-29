module;
#include "Internal.hpp"

export module Glib.Device.Colour:SystemColors;
import <type_traits>;

#define DEPRECATED_WIN10 [[deprecated("This colour has been deprecated since Windows 10.")]]

namespace gl::device
{
	using NativeColorBrush = HBRUSH;

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

#pragma region Deprecated
		__ActiveBorder DEPRECATED_WIN10 = COLOR_ACTIVEBORDER,
		__ActiveCaption DEPRECATED_WIN10 = COLOR_ACTIVECAPTION,
		__AppWorkspace DEPRECATED_WIN10 = COLOR_APPWORKSPACE,
		__Background DEPRECATED_WIN10 = COLOR_BACKGROUND,
		__BtnFace DEPRECATED_WIN10 = COLOR_BTNFACE,
		__BtnHighlight DEPRECATED_WIN10 = COLOR_BTNHIGHLIGHT,
		__BtnShadow DEPRECATED_WIN10 = COLOR_BTNSHADOW,
		__CaptionText DEPRECATED_WIN10 = COLOR_CAPTIONTEXT,
		__Desktop DEPRECATED_WIN10 = COLOR_DESKTOP,
		__GradientActiveCaption DEPRECATED_WIN10 = COLOR_GRADIENTACTIVECAPTION,
		__GradientInactiveCaption DEPRECATED_WIN10 = COLOR_GRADIENTINACTIVECAPTION,
		__InactiveBorder DEPRECATED_WIN10 = COLOR_INACTIVEBORDER,
		__InactiveCaption DEPRECATED_WIN10 = COLOR_INACTIVECAPTION,
		__InactiveCaptionText DEPRECATED_WIN10 = COLOR_INACTIVECAPTIONTEXT,
		__InfoBk DEPRECATED_WIN10 = COLOR_INFOBK,
		__InfoText DEPRECATED_WIN10 = COLOR_INFOTEXT,
		__Menu DEPRECATED_WIN10 = COLOR_MENU,
		__MenuText DEPRECATED_WIN10 = COLOR_MENUTEXT,
		__Scrollbar DEPRECATED_WIN10 = COLOR_SCROLLBAR,
		__WindowFrame DEPRECATED_WIN10 = COLOR_WINDOWFRAME,
#pragma endregion
	};

	export extern "C" namespace system_components
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
		NativeColorBrush stock;
	};

	export template<ColoredComponent Target>
	[[nodiscard]]
	inline const NativeColorBrush&
		GetComponentColor()
		noexcept(COLOR_WINDOW <= static_cast<int>(Target) <= COLOR_HOTLIGHT)
	{
		static InternalCColor<Target> stock = ::GetSysColorBrush(static_cast<int>(Target));
		return stock;
	}
}
