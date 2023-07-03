module;
#include "Internal.hpp"

export module Glib.Device.Brush;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	class [[nodiscard]] ColorBrush : public IHandle<native::NativeColorBrush>
	{
	public:
		using base = IHandle<native::NativeColorBrush>;

		constexpr ColorBrush() noexcept = default;

		constexpr ColorBrush(nullptr_t) noexcept
			: base(nullptr)
		{}

		explicit constexpr ColorBrush(const handle_type& brush) noexcept
			: base(brush)
		{}

		explicit constexpr ColorBrush(handle_type&& brush) noexcept
			: base(std::move(brush))
		{}

		~ColorBrush() noexcept
		{
			Destroy();
		}

		void Destroy() noexcept
		{
			if (nullptr != GetHandle())
			{
				Delegate(::DeleteObject);
				base::operator=(nullptr);
			}
		}

		constexpr ColorBrush& operator=(const handle_type& brush) noexcept
		{
			base::operator=(brush);
			return *this;
		}

		constexpr ColorBrush& operator=(handle_type&& brush) noexcept
		{
			base::operator=(std::move(brush));
			return *this;
		}

		ColorBrush& operator=(nullptr_t) noexcept
		{
			Destroy();

			return *this;
		}

		ColorBrush(const ColorBrush&) = delete;
		constexpr ColorBrush(ColorBrush&&) noexcept = default;
		ColorBrush& operator=(const ColorBrush&) = delete;
		constexpr ColorBrush& operator=(ColorBrush&&) noexcept = default;
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
}
