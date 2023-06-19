module;
#include <Windows.h>
export module Glib.Windows;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Handle;
export import Glib.Device.Context;

export namespace gl::device
{
	using Procedure = ::WNDPROC;

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

	[[nodiscard]]
	inline ProcessInstance GetWindowInstance(WindowsHandle handle) noexcept
	{
		return reinterpret_cast<ProcessInstance>(GetWindowLongPtr(handle, GWLP_HINSTANCE));
	}

	class [[nodiscard]] Property
	{
	public:

		WNDCLASSEXW myWindowClass;
	};

	class [[nodiscard]] Window
	{
	public:

	};
}
