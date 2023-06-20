module;
#include "Internal.hpp"

export module Glib.Windows;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Handle;
export import Glib.Device.Context;
import Utility.Monad;

export namespace gl::device
{
	using Procedure = ::WNDPROC;
	using Message = ::MSG;
	using DeviceClass = ::WNDCLASSEXW;

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

		template<size_t ClassNameSize, size_t MenuNameSize>
		explicit Property(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
		) noexcept
			: Property(handle, procedure
						, class_name
						, LoadIconW(handle, IDI_APPLICATION)
						, LoadIconW(handle, IDI_APPLICATION)
						, LoadCursorW(handle, IDC_ARROW)
						, (HBRUSH)(COLOR_WINDOW + 1)
						, nullptr)
		{}

		template<size_t ClassNameSize, size_t MenuNameSize>
		explicit constexpr Property(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t(&menu_name)[MenuNameSize]
		) noexcept
			: Property(handle, procedure
						, class_name
						, icon
						, small_icon
						, cursor
						, background
						, menu_name)
		{}


		template<size_t ClassNameSize, size_t MenuNameSize>
		explicit constexpr Property(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name) noexcept
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

		util::Monad<DeviceClass> Register() const noexcept
		{
			if (RegisterClassExW(&myWindowClass))
			{
				return myWindowClass;
			}
			else
			{
				return util::nullopt;
			}
		}

		[[nodiscard]]
		constexpr const DeviceClass& GetHandle() const& noexcept
		{
			return myWindowClass;
		}

		[[nodiscard]]
		constexpr DeviceClass&& GetHandle() && noexcept
		{
			return static_cast<DeviceClass&&>(myWindowClass);
		}

		constexpr Property(const Property&) noexcept = default;
		constexpr Property& operator=(const Property&) noexcept = default;
		constexpr Property(Property&&) noexcept = default;
		constexpr Property& operator=(Property&&) noexcept = default;

	private:
		DeviceClass myWindowClass;
	};

	class [[nodiscard]] Window
	{
	protected:
		Window(const Property& properties)
		{
			const auto& device_class = properties.GetHandle();
			myInstance = device_class.hInstance;

			const DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_ACTIVECAPTION;
			myHandle = DeviceHandle::Create(device_class.hInstance, device_class.lpszClassName, L"title", device_class.style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT);

			if (!myHandle.IsAvailable())
			{
				throw "Failed to create window.";
			}

			myContext = DeviceContext{ myHandle };
			if (!myContext)
			{
				throw "Failed to get device context.";
			}
		}

	public:
		virtual inline ~Window() noexcept
		{
			::ReleaseDC(myContext, myHandle);
			::UnregisterClass(myClassName, myInstance);
		}

		constexpr Window(const Window&) noexcept = delete;
		constexpr Window& operator=(const Window&) noexcept = delete;
		constexpr Window(Window&&) noexcept = default;
		constexpr Window& operator=(Window&&) noexcept = default;

		HINSTANCE myInstance;
		DeviceHandle myHandle;
		DeviceContext myContext;

		const wchar_t* myClassName;
	};
}
