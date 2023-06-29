module;
#include "Internal.hpp"

export module Glib.Device.Brush;
import <type_traits>;
export import Glib.Device.Colour;

#define DEPRECATED_WIN10 [[deprecated("This colour has been deprecated since Windows 10.")]]

namespace gl::device
{
	export using NativeColorBrush = HBRUSH;

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

	class [[nodiscard]] ColorBrush
	{
	public:
		constexpr ColorBrush() noexcept = default;

		~ColorBrush() noexcept
		{
			::DeleteObject(myBrush);
		}

		explicit constexpr ColorBrush(const NativeColorBrush& brush) noexcept
			: myBrush(brush)
		{}

		explicit constexpr ColorBrush(NativeColorBrush&& brush) noexcept
			: myBrush(std::move(brush))
		{}

		constexpr ColorBrush& operator=(const NativeColorBrush& brush) noexcept
		{
			myBrush = brush;
			return *this;
		}

		constexpr ColorBrush& operator=(NativeColorBrush&& brush) noexcept
		{
			myBrush = std::move(brush);
			return *this;
		}

		[[nodiscard]]
		constexpr const NativeColorBrush& GetHandle() const& noexcept
		{
			return myBrush;
		}

		[[nodiscard]]
		constexpr  NativeColorBrush&& GetHandle() && noexcept
		{
			return std::move(myBrush);
		}

		ColorBrush(const ColorBrush&) = delete;
		constexpr ColorBrush(ColorBrush&&) noexcept = default;
		ColorBrush& operator=(const ColorBrush&) = delete;
		constexpr ColorBrush& operator=(ColorBrush&&) noexcept = default;

		NativeColorBrush myBrush = nullptr;
	};

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
		GetComponentColor()
		noexcept(COLOR_WINDOW <= static_cast<int>(Target) && static_cast<int>(Target) <= COLOR_HOTLIGHT)
	{
		static InternalCColor<Target> stock = ::GetSysColorBrush(static_cast<int>(Target));
		return stock.myBrush;
	}

	export const NativeColorBrush&
		MakeDefaultComponentColor() noexcept
	{
		return GetComponentColor<colored_components::Background>();
	}

	[[nodiscard]]
	export NativeColorBrush MakeNativeBrush(const RawColour& color) noexcept
	{
		return ::CreateSolidBrush(color);
	}

	export NativeColorBrush MakeNativeBrush(RawColour&& color) noexcept
	{
		return ::CreateSolidBrush(std::move(color));
	}

	[[nodiscard]]
	export NativeColorBrush MakeNativePatternBrush(const HBITMAP& pattern_img) noexcept
	{
		return ::CreatePatternBrush(pattern_img);
	}

	export bool DeleteNativeBrush(NativeColorBrush& brush) noexcept
	{
		return 0 != ::DeleteObject(brush);
	}
}
