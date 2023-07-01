module;
#include "Internal.hpp"

export module Glib.Device.Brush;
import <type_traits>;
export import Glib.Device.Colour;

export namespace gl::device
{
	using NativeColorBrush = ::HBRUSH__*;

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

	[[nodiscard]]
	ColorBrush MakeColorBrush(const unsigned long& color) noexcept
	{
		return ColorBrush{ ::CreateSolidBrush(color) };
	}

	[[nodiscard]]
	ColorBrush MakeColorBrush(unsigned long&& color) noexcept
	{
		return ColorBrush{ ::CreateSolidBrush(std::move(color)) };
	}

	[[nodiscard]]
	ColorBrush MakePatternBrush(const HBITMAP& pattern_img) noexcept
	{
		return ColorBrush{ ::CreatePatternBrush(pattern_img) };
	}

	[[nodiscard]]
	NativeColorBrush MakeNativeBrush(const unsigned long& color) noexcept
	{
		return ::CreateSolidBrush(color);
	}

	[[nodiscard]]
	NativeColorBrush MakeNativeBrush(unsigned long&& color) noexcept
	{
		return ::CreateSolidBrush(std::move(color));
	}

	export bool DeleteNativeBrush(NativeColorBrush& brush) noexcept
	{
		return 0 != ::DeleteObject(brush);
	}
}
