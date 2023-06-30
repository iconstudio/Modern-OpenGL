module;
#include "Internal.hpp"

export module Glib.Device.Brush;
import <type_traits>;
export import Glib.Device.Colour;

namespace gl::device
{
	export using NativeColorBrush = ::HBRUSH__*;

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

	export class [[nodiscard]] ColorBrush
	{
	public:
		constexpr ColorBrush() noexcept = default;

		~ColorBrush() noexcept
		{
			::DeleteObject(myBrush);
		}

		explicit ColorBrush(const int& component_id) noexcept
			: myBrush(::GetSysColorBrush(component_id))
		{}

		explicit ColorBrush(int&& component_id) noexcept
			: myBrush(::GetSysColorBrush(component_id))
		{}

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
		constexpr NativeColorBrush&& GetHandle() && noexcept
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

	export
		[[nodiscard]]
	NativeColorBrush MakeNativeBrush(const RawColour& color) noexcept
	{
		return ::CreateSolidBrush(color);
	}

	export
		[[nodiscard]]
	NativeColorBrush MakeNativeBrush(RawColour&& color) noexcept
	{
		return ::CreateSolidBrush(std::move(color));
	}

	export
		[[nodiscard]]
	NativeColorBrush MakeNativeBrush(const Colour& color) noexcept
	{
		return ::CreateSolidBrush(color.ToRaw());
	}

	export
		[[nodiscard]]
	NativeColorBrush MakeNativeBrush(Colour&& color) noexcept
	{
		return ::CreateSolidBrush(color.ToRaw());
	}

	export
		[[nodiscard]]
	NativeColorBrush MakeNativePatternBrush(const HBITMAP& pattern_img) noexcept
	{
		return ::CreatePatternBrush(pattern_img);
	}

	export bool DeleteNativeBrush(NativeColorBrush& brush) noexcept
	{
		return 0 != ::DeleteObject(brush);
	}

	export
		[[nodiscard]]
	ColorBrush MakeColorBrush(const RawColour& color) noexcept
	{
		return ColorBrush{ ::CreateSolidBrush(color) };
	}

	export
		[[nodiscard]]
	ColorBrush MakeColorBrush(RawColour&& color) noexcept
	{
		return ColorBrush{ ::CreateSolidBrush(std::move(color)) };
	}

	export
		[[nodiscard]]
	ColorBrush MakePatternBrush(const HBITMAP& pattern_img) noexcept
	{
		return ColorBrush{ ::CreatePatternBrush(pattern_img) };
	}
}
