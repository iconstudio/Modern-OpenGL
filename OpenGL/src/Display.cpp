module;
#include <Windows.h>
#include <dwmapi.h>
#include <winrt/windows.devices.display.h>
#include <winrt/windows.ui.composition.h>
#include <winrt/Windows.ui.viewmanagement.h>

module Glib.Display;
import Glib.Rect;
import Glib.Windows.Colour;

using namespace winrt::Windows::UI::ViewManagement;

namespace gl::display
{
	using DisplayProperty = winrt::Windows::UI::ViewManagement::UISettings;

	[[nodiscard]]
	DisplayProperty AcquireSettings() noexcept;

	namespace dpi
	{
		bool SetDPIAware(const bool& enable) noexcept
		{
			if (enable)
			{
				// Sharp
				// Also calls EnableNonClientDpiScaling
				return 0 != ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
			}
			else
			{
				// Little Blurry
				return 0 != ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
			}
		}

		DpiAwareness Convert(const DPI_AWARENESS&& awareness) noexcept
		{
			switch (awareness)
			{
				case DPI_AWARENESS_UNAWARE: return DpiAwareness::Unaware;
				case DPI_AWARENESS_SYSTEM_AWARE: return DpiAwareness::System;
				case DPI_AWARENESS_PER_MONITOR_AWARE: return DpiAwareness::Aware;
				//case DPI_AWARENESS_PER_MONITOR_AWARE_V2: return DpiAwareness::PerMonitorAwareV2;
				//case DPI_AWARENESS_UNAWARE_GDISCALED: return DpiAwareness::UnawareGDIScaled;
				default:
				{
					return DpiAwareness::Unaware;
				}
			}
		}

		DpiAwareness GetDPIAware() noexcept
		{
			DPI_AWARENESS_CONTEXT context = ::GetThreadDpiAwarenessContext();
			if (::IsValidDpiAwarenessContext(context))
			{
				return Convert(::GetAwarenessFromDpiAwarenessContext(context));
			}

			return DpiAwareness::Unaware;
		}

		bool IsDPIAware() noexcept
		{
			return DpiAwareness::Aware == GetDPIAware();
		}

		DpiAwareness GetDPIAware(const HWND& handle) noexcept
		{
			DPI_AWARENESS_CONTEXT context = ::GetWindowDpiAwarenessContext(handle);
			if (::IsValidDpiAwarenessContext(context))
			{
				return Convert(::GetAwarenessFromDpiAwarenessContext(context));
			}

			return DpiAwareness::Unaware;
		}

		bool IsDPIAware(const HWND& handle) noexcept
		{
			return DpiAwareness::Aware == GetDPIAware(handle);
		}

		unsigned int GetDPI() noexcept
		{
			DPI_AWARENESS_CONTEXT context = ::GetThreadDpiAwarenessContext();
			if (::IsValidDpiAwarenessContext(context))
			{
				return ::GetDpiFromDpiAwarenessContext(context);
			}
			else
			{
				return 96;
			}
		}
	}

	Rect GetActualDisplaySize() noexcept
	{
		return Rect{ 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN) };
	}

	Rect GetDisplaySize() noexcept
	{
		const unsigned int dpi = dpi::GetDPI();

		return Rect{ 0, 0, ::GetSystemMetricsForDpi(SM_CXSCREEN, dpi), ::GetSystemMetricsForDpi(SM_CYSCREEN, dpi) };
	}

	bool IsDimmingMode()
	{
		DisplayProperty settings = AcquireSettings();
		//const win32::Colour col_a_0 = settings.GetColorValue(UIColorType::Accent);
		//const win32::Colour col_a_1 = settings.GetColorValue(UIColorType::AccentDark1);
		//const win32::Colour col_a_2 = settings.GetColorValue(UIColorType::AccentDark2);
		//const win32::Colour col_a_3 = settings.GetColorValue(UIColorType::AccentDark3);
		//const win32::Colour col_a_4 = settings.GetColorValue(UIColorType::AccentLight1);
		//const win32::Colour col_a_5 = settings.GetColorValue(UIColorType::AccentLight2);
		//const win32::Colour col_a_6 = settings.GetColorValue(UIColorType::AccentLight3);
		const win32::Colour col_fg = settings.GetColorValue(UIColorType::Foreground);
		//const win32::Colour col_bk = settings.GetColorValue(UIColorType::Background);

		if (win32::IsColorBright(col_fg))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	DisplayProperty AcquireSettings() noexcept
	{
		return {};
	}
}
