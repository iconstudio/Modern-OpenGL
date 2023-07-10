module;
#include <Windows.h>
#undef USER_DEFAULT_SCREEN_DPI

export module Glib.Display;
import <utility>;
import Utility;
export import Glib.Rect;
export import Glib.Device.Colour;

namespace gl::display
{
	export enum class [[nodiscard]] DpiAwareness
	{
		Invalid = ::DPI_AWARENESS_INVALID,
		Unaware = ::DPI_AWARENESS_UNAWARE,
		System = ::DPI_AWARENESS_SYSTEM_AWARE,
		Aware = ::DPI_AWARENESS_PER_MONITOR_AWARE
	};

	export namespace dpi
	{
		constexpr UINT DEFAULT_DPI = 96U;

		bool SetDPIAware(const bool& enable) noexcept;
		[[nodiscard]] bool IsDPIAware() noexcept;
		[[nodiscard]] DpiAwareness GetDPIAware() noexcept;
		[[nodiscard]] bool IsDPIAware(const HWND& handle) noexcept;
		[[nodiscard]] consteval unsigned int GetDefaultDPI() noexcept { return DEFAULT_DPI; }
		[[nodiscard]] DpiAwareness GetDPIAware(const HWND& handle) noexcept;
		[[nodiscard]] unsigned int GetDPI() noexcept;
	}

	export [[nodiscard]] Rect GetActualDisplaySize() noexcept;
	export [[nodiscard]] Rect GetDisplaySize() noexcept;
	export [[nodiscard]] bool IsDimmingMode();
	export [[nodiscard]] HDC GetDisplayContext() noexcept;
}
