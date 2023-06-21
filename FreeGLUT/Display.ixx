module;
#include "Internal.hpp"

#undef USER_DEFAULT_SCREEN_DPI
export module Glib.Device.Display;
import Utility;
import Utility.Traits;
import <utility>;
import <numeric>;
import <limits>;

namespace gl::device
{
	[[nodiscard]]
	constexpr int abs(const int& value) noexcept
	{
		return 0 < value ? value : -value;
	}

	[[nodiscard]]
	constexpr const unsigned int& abs(const unsigned int& value) noexcept
	{
		return value;
	}

	[[nodiscard]]
	constexpr unsigned int&& abs(unsigned int&& value) noexcept
	{
		return static_cast<unsigned int&&>(value);
	}

	[[nodiscard]]
	constexpr long long abs(const long long& value) noexcept
	{
		return 0 < value ? value : -value;
	}

	[[nodiscard]]
	constexpr const unsigned long long& abs(const unsigned long long& value) noexcept
	{
		return value;
	}

	[[nodiscard]]
	constexpr unsigned long long&& abs(unsigned long long&& value) noexcept
	{
		return static_cast<unsigned long long&&>(value);
	}

	[[nodiscard]]
	constexpr int sign(const int& value) noexcept
	{
		return 0 < value ? 1 : (value < 0 ? -1 : 0);
	}

	[[nodiscard]]
	constexpr int sign(const unsigned int& value) noexcept
	{
		return 1;
	}

	[[nodiscard]]
	constexpr int sign(const long long& value) noexcept
	{
		return 0 < value ? 1 : (value < 0 ? -1 : 0);
	}

	[[nodiscard]]
	constexpr int sign(const unsigned long long& value) noexcept
	{
		return 1;
	}

	[[nodiscard]]
	constexpr auto SafeDenom(const auto& value, const auto& mul, const auto& div)
	{
		int tval;
		int tmul;
		int tdiv;

		const int& signs = sign(value) * sign(mul) * sign(div);
		if (0 == signs)
		{
			if (0 == div)
			{
				static_assert(util::always_false<decltype(div)>, "div is zero");

				throw NAN;
			}
			else
			{
				return 0;
			}
		}
		else if (signs == 1)
		{
			tval = gl::device::abs(value);
			tmul = gl::device::abs(mul);
			tdiv = gl::device::abs(div);
		}
		else
		{
			tval = gl::device::abs(value);
			tmul = gl::device::abs(mul);
			// push all signs to div
			tdiv = gl::device::abs(div) * signs;
		}

		if (tval < tmul)
		{
			const double mdiv = static_cast<double>(tmul) / tdiv;

			return static_cast<int>(mdiv * tval);
		}
		else
		{
			const double vdiv = static_cast<double>(tval) / tdiv;

			return static_cast<int>(vdiv * tmul);
		}
	}

	void test_safe_denom()
	{
		constexpr auto aaa = SafeDenom(754638, -6352, 1);
		constexpr auto bbb = SafeDenom(754638, -6352, 10);
		constexpr auto ccc = SafeDenom(754638, -6352, 100);
		constexpr auto ddd = SafeDenom(754638, -6352, 1000);
		constexpr auto eee = SafeDenom(754638, -6352, 10000);
		constexpr auto fff = SafeDenom(754638, -6352, 100000);
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
			static constexpr wchar_t hKey[] = L"HKCU\\SOFTWARE\\Microsoft\\Accessibility";
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
