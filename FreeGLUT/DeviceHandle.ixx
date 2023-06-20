module;
#include "Internal.hpp"

export module Glib.Device.Handle;
import Utility.Atomic;

export namespace gl::device
{
	using ::HWND, ::HMENU, ::PVOID, ::LPVOID;
	using RawDeviceHandle = ::HWND;

	using ::GetLastError;

	class [[nodiscard]] DeviceHandle
	{
	public:
		constexpr DeviceHandle() noexcept = default;

		constexpr DeviceHandle(RawDeviceHandle&& handle) noexcept
			: myHandle(static_cast<RawDeviceHandle&&>(handle))
		{}

		constexpr DeviceHandle(volatile RawDeviceHandle&& handle) noexcept
			: myHandle(static_cast<volatile RawDeviceHandle&&>(handle))
		{}

		virtual ~DeviceHandle() noexcept
		{
			if (myHandle)
			{
				::DestroyWindow(myHandle);
				myHandle = nullptr;
			}
		}

		constexpr DeviceHandle& operator=(RawDeviceHandle&& handle) noexcept
		{
			myHandle = static_cast<RawDeviceHandle&&>(handle);
			return *this;
		}

		constexpr DeviceHandle& operator=(volatile RawDeviceHandle&& handle) noexcept
		{
			myHandle = static_cast<volatile RawDeviceHandle&&>(handle);
			return *this;
		}

		[[nodiscard]]
		inline const volatile RawDeviceHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline volatile RawDeviceHandle&& GetHandle() && noexcept
		{
			return static_cast<volatile RawDeviceHandle&&>(myHandle);
		}

		constexpr operator RawDeviceHandle() const noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr bool operator==(const DeviceHandle& rhs) const noexcept
		{
			return myHandle == rhs.myHandle;
		}

		DeviceHandle(const DeviceHandle&) = delete;
		constexpr DeviceHandle(DeviceHandle&&) noexcept = default;
		DeviceHandle& operator=(const DeviceHandle&) = delete;
		constexpr DeviceHandle& operator=(DeviceHandle&&) noexcept = default;

		volatile RawDeviceHandle myHandle;
	};


#define     DeletePen(hpen)      DeleteObject((HGDIOBJ)(HPEN)(hpen))
#define     SelectPen(hdc, hpen)    ((HPEN)SelectObject((hdc), (HGDIOBJ)(HPEN)(hpen)))
#define     GetStockPen(i)       ((HPEN)GetStockObject(i))

#define     DeleteBrush(hbr)     DeleteObject((HGDIOBJ)(HBRUSH)(hbr))
#define     SelectBrush(hdc, hbr)   ((HBRUSH)SelectObject((hdc), (HGDIOBJ)(HBRUSH)(hbr)))
#define     GetStockBrush(i)     ((HBRUSH)GetStockObject(i))

#define     DeleteRgn(hrgn)      DeleteObject((HGDIOBJ)(HRGN)(hrgn))

#define     CopyRgn(hrgnDst, hrgnSrc)               CombineRgn(hrgnDst, hrgnSrc, 0, RGN_COPY)
#define     IntersectRgn(hrgnResult, hrgnA, hrgnB)  CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_AND)
#define     SubtractRgn(hrgnResult, hrgnA, hrgnB)   CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_DIFF)
#define     UnionRgn(hrgnResult, hrgnA, hrgnB)      CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_OR)
#define     XorRgn(hrgnResult, hrgnA, hrgnB)        CombineRgn(hrgnResult, hrgnA, hrgnB, RGN_XOR)

#define     DeletePalette(hpal)     DeleteObject((HGDIOBJ)(HPALETTE)(hpal))

#define     DeleteFont(hfont)            DeleteObject((HGDIOBJ)(HFONT)(hfont))
#define     SelectFont(hdc, hfont)  ((HFONT)SelectObject((hdc), (HGDIOBJ)(HFONT)(hfont)))
#define     GetStockFont(i)      ((HFONT)GetStockObject(i))

#define     DeleteBitmap(hbm)       DeleteObject((HGDIOBJ)(HBITMAP)(hbm))
#define     SelectBitmap(hdc, hbm)  ((HBITMAP)SelectObject((hdc), (HGDIOBJ)(HBITMAP)(hbm)))

#define     InsetRect(lprc, dx, dy) InflateRect((lprc), -(dx), -(dy))

#define  MapWindowRect(hwndFrom, hwndTo, lprc) \
                    MapWindowPoints((hwndFrom), (hwndTo), (POINT *)(lprc), 2)

#define IsLButtonDown()  (GetKeyState(VK_LBUTTON) < 0)
#define IsRButtonDown()  (GetKeyState(VK_RBUTTON) < 0)
#define IsMButtonDown()  (GetKeyState(VK_MBUTTON) < 0)
}
