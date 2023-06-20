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
	protected:
		explicit constexpr DeviceHandle(RawDeviceHandle&& handle)
			noexcept
			: myHandle(static_cast<RawDeviceHandle&&>(handle))
		{}

	public:
		template<size_t ClassLength, size_t TitleLength>
		[[nodiscard]]
		static DeviceHandle Create(const ::HINSTANCE& instance
			, _Notnull_ const wchar_t(&class_name)[ClassLength]
			, _Notnull_ const wchar_t(&title)[TitleLength]
			, const unsigned int& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
			, const RawDeviceHandle& parent = nullptr
			, const HMENU& menu = nullptr
			, const LPVOID& uparams = nullptr)
			noexcept
		{
			return DeviceHandle
			{
				::CreateWindowEx(0
				, class_name, title
				, style, x, y, width, height
				, parent
				, menu
				, instance, uparams)
			};
		}

		template<size_t ClassLength, size_t TitleLength>
		[[nodiscard]]
		static DeviceHandle Create(const ::HINSTANCE& instance
			, _Notnull_ const wchar_t(&class_name)[ClassLength]
			, _Notnull_ const wchar_t(&title)[TitleLength]
			, const unsigned int& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
			, const DeviceHandle& parent
			, const HMENU& menu = nullptr
			, const LPVOID& uparams = nullptr)
			noexcept
		{
			return Create(instance, class_name, title, style, x, y, width, height, parent.GetHandle(), menu, uparams);
		}

		[[nodiscard]]
		static DeviceHandle Create(const ::HINSTANCE& instance
			, _Notnull_ const wchar_t* const& class_name
			, _Notnull_ const wchar_t* const& title
			, const unsigned int& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
			, const RawDeviceHandle& parent = nullptr
			, const HMENU& menu = nullptr
			, const LPVOID& uparams = nullptr)
			noexcept
		{
			return DeviceHandle
			{
				::CreateWindowEx(0
				, class_name, title
				, style, x, y, width, height
				, parent
				, menu
				, instance, uparams)
			};
		}

		constexpr DeviceHandle() noexcept = default;

		virtual ~DeviceHandle() noexcept
		{
			if (myHandle)
			{
				::DestroyWindow(myHandle);
				myHandle = nullptr;
			}
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
