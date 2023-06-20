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

		inline bool SendCommand(const unsigned int& msg, const WPARAM& lhs, const LPARAM& rhs) const
			noexcept
		{
			return 0 != ::PostMessage(myHandle, msg, lhs, rhs);
		}

		inline bool SendCommand(const unsigned int& msg) const
			noexcept
		{
			return SendCommand(msg, 0, 0);
		}

		inline bool SetWindowRedraw(const bool& flag) noexcept
		{
			return SendCommand(WM_SETREDRAW, static_cast<WPARAM>(flag), 0);
		}

		inline bool Close() noexcept
		{
			if (bool result = SendCommand(WM_CLOSE); result)
			{
				return result;
			}
			else
			{
				return false;
			}
		}

		inline bool Show(const int& cmd_show) noexcept
		{
			return SendCommand(WM_SHOWWINDOW, static_cast<WPARAM>(cmd_show), 0);
		}

		inline bool Hide() noexcept
		{
			return Show(SW_HIDE);
		}

		inline bool Maximize() noexcept
		{
			return Show(SW_MAXIMIZE);
		}

		inline bool Minimize() noexcept
		{
			return Show(SW_MINIMIZE);
		}

		inline bool Restore() noexcept
		{
			return Show(SW_RESTORE);
		}

		inline bool MakeFocus() noexcept
		{
			return SendCommand(WM_SETFOCUS);
		}

		inline bool MakeForeground() noexcept
		{
			return SendCommand(WM_ACTIVATE, WA_ACTIVE, 0);
		}

		[[nodiscard]]
		inline bool IsMinimized() const noexcept
		{
			return 0 != IsIconic(myHandle);
		}

		[[nodiscard]]
		inline bool IsMaximized() const noexcept
		{
			return 0 != IsZoomed(myHandle);
		}

		[[nodiscard]]
		inline bool IsRestored() const noexcept
		{
			return 0L == (GetStyle() & (WS_MINIMIZE | WS_MAXIMIZE));
		}

		[[nodiscard]]
		inline DWORD GetStyle() const noexcept
		{
			return static_cast<DWORD>(GetWindowLongPtr(myHandle, GWL_STYLE));
		}

		[[nodiscard]]
		inline DWORD GetExStyle() const noexcept
		{
			return static_cast<DWORD>(GetWindowLongPtr(myHandle, GWL_EXSTYLE));
		}

		[[nodiscard]]
		inline int GetID() const noexcept
		{
			return static_cast<int>(GetWindowLongPtr(myHandle, GWLP_ID));
		}

		[[nodiscard]]
		inline RawDeviceHandle GetOwner() const noexcept
		{
			return ::GetWindow(myHandle, GW_OWNER);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetFirstChild() const noexcept
		{
			return ::GetTopWindow(myHandle);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetFirstSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDFIRST);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetLastChild() const noexcept
		{
			return ::GetWindow(myHandle, GW_CHILD);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetLastSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDLAST);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetNextSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDNEXT);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetPrevSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDPREV);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetWindowParent() const noexcept
		{
			return ::GetParent(myHandle);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetWindowRoot() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOT);
		}

		[[nodiscard]]
		inline RawDeviceHandle GetWindowRootOwner() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOTOWNER);
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
