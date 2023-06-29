module;
#include "Internal.hpp"

#undef USER_DEFAULT_SCREEN_DPI
export module Glib.Device.Display;
import <utility>;
import Utility;
export import Glib.Device.Colour;

namespace gl::device
{
	export namespace dim
	{
		void FindDimmingMode();
	}

	export namespace dpi
	{
		constexpr UINT USER_DEFAULT_SCREEN_DPI = 96;

		using ::DPI_AWARENESS;
		using ::DPI_AWARENESS_CONTEXT__, ::DPI_AWARENESS_CONTEXT;

#if 0
		void testss()
		{
			DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2;
			wchar_t result[50];
			wchar_t awareness[50];
			wchar_t awarenessContext[50];

			// Get the DPI awareness of the window from the DPI-awareness context of the thread
			DPI_AWARENESS_CONTEXT dpiAwarenessContext = GetThreadDpiAwarenessContext();
			DPI_AWARENESS dpiAwareness = GetAwarenessFromDpiAwarenessContext(dpiAwarenessContext);
		}

		UINT GetDPI(HWND hWnd)
		{
			if (hWnd != NULL)
			{
				if (pfnGetDpiForWindow)
					return pfnGetDpiForWindow(hWnd);
			}
			else
			{
				if (pfnGetDpiForSystem)
					return pfnGetDpiForSystem();
			}

			if (HDC hDC = GetDC(hWnd))
			{
				auto dpi = GetDeviceCaps(hDC, LOGPIXELSX);
				ReleaseDC(hWnd, hDC);
				return dpi;
			}
			else
			{
				return USER_DEFAULT_SCREEN_DPI;
			}
		}

		DWORD GetCurrentTextScaleFactor() const
		{
			static inline constexpr wchar_t hKey[] = L"HKCU\\SOFTWARE\\Microsoft\\Accessibility";
			static HANDLE hEvent = NULL;

			if (hKey)
			{
				RegCloseKey(hKey);
				hKey = NULL;
			}
			if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Accessibility", 0, KEY_NOTIFY | KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
			{
				if (RegNotifyChangeKeyValue(hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, this->hEvent, TRUE) == ERROR_SUCCESS)
				{
					return true;
		}
	}
			else
			{
				if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft", 0, KEY_NOTIFY, &hKey) == ERROR_SUCCESS)
				{
					if (RegNotifyChangeKeyValue(this->hKey, FALSE, REG_NOTIFY_CHANGE_NAME, this->hEvent, TRUE) == ERROR_SUCCESS)
					{
						return true;
					}
				}
			}

			DWORD scale;
			DWORD cb = sizeof scale;

			if (RegQueryValueEx(hKey, L"TextScaleFactor", NULL, NULL, (LPBYTE)&scale, &cb) == ERROR_SUCCESS)
			{
				return scale;
			}
			else
				return 100;
}
#endif
	}

	namespace display
	{
		namespace this_device
		{
			static void* context = nullptr;
		}
	}
}
