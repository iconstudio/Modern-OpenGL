module;
#include <Windows.h>
export module Glib.Windows;

export namespace gl::device
{
	using ProcessInstance = ::HINSTANCE;
	using WindowsContext = ::HWND;
	using Procedure = ::WNDPROC;
	using DeviceContext = ::HDC;
	using GrpContext = ::HGLRC;
	using GrpDescriptor = ::PIXELFORMATDESCRIPTOR;

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


#if (WINVER >= 0x030a)
#define  MapWindowRect(hwndFrom, hwndTo, lprc) \
                    MapWindowPoints((hwndFrom), (hwndTo), (POINT *)(lprc), 2)
#endif
#define IsLButtonDown()  (GetKeyState(VK_LBUTTON) < 0)
#define IsRButtonDown()  (GetKeyState(VK_RBUTTON) < 0)
#define IsMButtonDown()  (GetKeyState(VK_MBUTTON) < 0)

	[[nodiscard]]
	inline ProcessInstance GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(nullptr);
	}

	[[nodiscard]]
	inline bool TryGetProcessInstance(ProcessInstance* &output) noexcept
	{
		return 0 != ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, output);
	}

	[[nodiscard]]
	inline bool TryGetProcessInstance(ProcessInstance& output) noexcept
	{
		return 0 != ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, &output);
	}

	[[nodiscard]]
	inline ProcessInstance GetWindowInstance(WindowsContext handle) noexcept
	{
		return reinterpret_cast<ProcessInstance>(GetWindowLongPtr(handle, GWLP_HINSTANCE));
	}

	class [[nodiscard]] WindowHandle
	{
	public:
		template<size_t Length>
		constexpr WindowHandle(ProcessInstance instance
			, WindowsContext&& handle
			, const wchar_t(&class_name)[Length])
			noexcept
			: WindowHandle(instance, static_cast<WindowsContext&&>(handle), class_name)
		{}

		constexpr WindowHandle(ProcessInstance instance
			, WindowsContext&& handle
			, const wchar_t* const& class_name)
			noexcept
			: myInstance(instance)
			, myHandle(static_cast<WindowsContext&&>(handle))
			, myClassName(class_name)
		{}

		virtual ~WindowHandle() noexcept
		{
			if (myHandle)
			{
				::DestroyWindow(myHandle);

				myHandle = nullptr;
			}

			if (myInstance)
			{
				::UnregisterClass(myClassName, myInstance);
			}
		}

		LRESULT SendMsg(const unsigned int& msg, const WPARAM& lhs, const LPARAM& rhs) const
			noexcept
		{
			return ::SendMessage(myHandle, msg, lhs, rhs);
		}

		void SetWindowRedraw(const bool& flag) noexcept
		{
			SendMsg(WM_SETREDRAW, static_cast<WPARAM>(flag), 0);
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
		inline WindowsContext GetOwner() const noexcept
		{
			return ::GetWindow(myHandle, GW_OWNER);
		}

		[[nodiscard]]
		inline WindowsContext GetFirstChild() const noexcept
		{
			return ::GetTopWindow(myHandle);
		}

		[[nodiscard]]
		inline WindowsContext GetFirstSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDFIRST);
		}

		[[nodiscard]]
		inline WindowsContext GetLastChild() const noexcept
		{
			return ::GetWindow(myHandle, GW_CHILD);
		}

		[[nodiscard]]
		inline WindowsContext GetLastSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDLAST);
		}

		[[nodiscard]]
		inline WindowsContext GetNextSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDNEXT);
		}

		[[nodiscard]]
		inline WindowsContext GetPrevSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDPREV);
		}

		[[nodiscard]]
		inline WindowsContext GetWindowParent() const noexcept
		{
			return ::GetParent(myHandle);
		}

		[[nodiscard]]
		inline WindowsContext GetWindowRoot() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOT);
		}

		[[nodiscard]]
		inline WindowsContext GetWindowRootOwner() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOTOWNER);
		}

		[[nodiscard]]
		inline const ProcessInstance& GetInstance() const& noexcept
		{
			return myInstance;
		}

		[[nodiscard]]
		inline ProcessInstance&& GetInstance() && noexcept
		{
			return static_cast<ProcessInstance&&>(myInstance);
		}

		[[nodiscard]]
		inline const WindowsContext& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline WindowsContext&& GetHandle() && noexcept
		{
			return static_cast<WindowsContext&&>(myHandle);
		}

		[[nodiscard]]
		constexpr bool operator==(const WindowHandle& rhs) const noexcept
		{
			return myHandle == rhs.myHandle;
		}

		WindowHandle(const WindowHandle&) = delete;
		constexpr WindowHandle(WindowHandle&&) noexcept = default;
		WindowHandle& operator=(const WindowHandle&) = delete;
		constexpr WindowHandle& operator=(WindowHandle&&) noexcept = default;

		ProcessInstance myInstance;
		WindowsContext myHandle;
		const wchar_t* myClassName;
	};

	class [[nodiscard]] Property
	{
	public:

		WNDCLASSEXW myWindowClass;
	};

	class [[nodiscard]] Context
	{
	public:
		explicit Context(WindowHandle& hwnd) noexcept
			: myWindow(hwnd)
			, myHandle(::GetDC(hwnd.myHandle))
		{}

		explicit constexpr Context(WindowHandle& hwnd, DeviceContext&& handle) noexcept
			: myWindow(hwnd)
			, myHandle(static_cast<DeviceContext&&>(handle))
		{}

		inline ~Context() noexcept
		{
			::ReleaseDC(myWindow.GetHandle(), myHandle);
		}

		[[nodiscard]]
		inline const DeviceContext& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline DeviceContext&& GetHandle() && noexcept
		{
			return static_cast<DeviceContext&&>(myHandle);
		}

		constexpr Context(Context&& other) noexcept
			: myWindow(other.myWindow)
			, myHandle(static_cast<DeviceContext&&>(other.myHandle))
		{}

		constexpr Context& operator=(Context&& other) & noexcept
		{
			if (this != &other && myWindow == other.myWindow)
			{
				myHandle = static_cast<DeviceContext&&>(other.myHandle);
			}
			return *this;
		}

		Context(const Context&) = delete;
		Context& operator=(const Context&) = delete;
		Context(const Context&&) = delete;
		Context& operator=(const Context&&) = delete;

		WindowHandle& myWindow;
		DeviceContext myHandle;
	};
}
