module;
#include "Internal.hpp"

export module Glib.Device.Window;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Handle;
export import Glib.Device.Context;
export import :Property;

export namespace gl::device
{
	using Message = ::MSG;

	using ::GetLastError;

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

	class [[nodiscard]] Window
	{
	protected:
		Window(const DeviceProperty& properties)
		{
			const auto& device_class = properties.GetHandle();
			myInstance = device_class.hInstance;

			const DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_ACTIVECAPTION;
			myHandle = DeviceHandle::Create(device_class.hInstance, device_class.lpszClassName, L"title", device_class.style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT);

			if (!myHandle.IsAvailable())
			{
				throw "Failed to create window.";
			}
		}

	public:
		virtual inline ~Window() noexcept
		{
			//::ReleaseDC(myContext, myHandle);
			::UnregisterClass(myClassName, myInstance);
		}

		[[nodiscard]]


		[[nodiscard]]
		constexpr const DeviceHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr DeviceHandle&& GetHandle() && noexcept
		{
			return static_cast<DeviceHandle&&>(myHandle);
		}

		[[nodiscard]]
		constexpr const wchar_t* const& GetClass() const& noexcept
		{
			return myClassName;
		}

		[[nodiscard]]
		constexpr const wchar_t*&& GetClass() && noexcept
		{
			return static_cast<const wchar_t*&&>(myClassName);
		}

		[[nodiscard]]

		constexpr Window(const Window&) noexcept = delete;
		constexpr Window& operator=(const Window&) noexcept = delete;
		constexpr Window(Window&&) noexcept = default;
		constexpr Window& operator=(Window&&) noexcept = default;

		HINSTANCE myInstance;
		DeviceHandle myHandle;

		const wchar_t* myClassName;
	};
}
