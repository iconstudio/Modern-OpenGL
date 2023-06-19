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

	class [[nodiscard]] Property
	{
	public:
		constexpr Property() noexcept = default;
		constexpr ~Property() noexcept = default;

		template<size_t ClassNameSize, size_t TitleSize, size_t MenuNameSize>
		Property(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const wchar_t(&title)[TitleSize]
			, const int& cmd_show) noexcept
			: Property(handle, procedure
							, class_name
							, title
							, LoadIconW(nullptr, IDI_APPLICATION)
							, LoadIconW(nullptr, IDI_APPLICATION)
							, LoadCursorW(nullptr, IDC_ARROW)
							, (HBRUSH)(COLOR_WINDOW + 1)
							, nullptr
							, cmd_show)
		{}

		template<size_t ClassNameSize, size_t TitleSize, size_t MenuNameSize>
		constexpr Property(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const wchar_t(&title)[TitleSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t(&menu_name)[MenuNameSize]
			, const int& cmd_show) noexcept
		{
			myWindowClass.cbSize = sizeof(WNDCLASSEXW);
			myWindowClass.hInstance = handle;
			myWindowClass.lpszClassName = class_name;
			myWindowClass.lpfnWndProc = procedure;
			myWindowClass.cbClsExtra = 0;
			myWindowClass.cbWndExtra = 0;
			myWindowClass.style = CS_HREDRAW | CS_VREDRAW;
			myWindowClass.hbrBackground = background;
			myWindowClass.lpszMenuName = menu_name;
			myWindowClass.hIcon = icon;
			myWindowClass.hIconSm = small_icon;
			myWindowClass.hCursor = cursor;
		}

		[[nodiscard]]
		constexpr const WNDCLASSEXW& GetHandle() const& noexcept
		{
			return myWindowClass;
		}

		[[nodiscard]]
		constexpr WNDCLASSEXW&& GetHandle() && noexcept
		{
			return static_cast<WNDCLASSEXW&&>(myWindowClass);
		}

		constexpr Property(const Property&) noexcept = default;
		constexpr Property& operator=(const Property&) noexcept = default;
		constexpr Property(Property&&) noexcept = default;
		constexpr Property& operator=(Property&&) noexcept = default;

	private:
		WNDCLASSEXW myWindowClass;
	};

	class [[nodiscard]] Window
	{
	public:

	};
}
