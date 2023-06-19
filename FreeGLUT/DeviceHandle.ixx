module;
#include <Windows.h>

export module Glib.Device.Handle;
import Utility.Atomic;

export namespace gl::device
{
	using ::HWND, ::HMENU, ::PVOID, ::LPVOID;
	using WindowsHandle = ::HWND;

	using ::GetLastError;

	class [[nodiscard]] DeviceHandle
	{
	protected:
		explicit constexpr DeviceHandle(WindowsHandle&& handle)
			noexcept
			: myHandle(static_cast<WindowsHandle&&>(handle))
			, isAvailable(true)
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
			, const WindowsHandle& parent = nullptr
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

		virtual ~DeviceHandle() noexcept
		{
			if (myHandle)
			{
				isAvailable = false;

				::DestroyWindow(myHandle);
				myHandle = nullptr;
			}
		}

		inline bool SendCommand(const unsigned int& msg) const
			noexcept
		{
			return SendCommand(myHandle, msg, 0, 0);
		}

		inline bool SendCommand(const unsigned int& msg, const WPARAM& lhs, const LPARAM& rhs) const
			noexcept
		{
			if (IsAvailable())
			{
				return 0 != ::PostMessage(myHandle, msg, lhs, rhs);
			}
			else
			{
				return false;
			}
		}

		inline bool SetWindowRedraw(const bool& flag) noexcept
		{
			return SendCommand(WM_SETREDRAW, static_cast<WPARAM>(flag), 0);
		}

		inline bool Close() noexcept
		{
			if (bool result = SendCommand(WM_CLOSE); result)
			{
				isAvailable = false;
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
		inline bool IsAvailable() const noexcept
		{
			return isAvailable.load(util::memory_order_relaxed);
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
		inline WindowsHandle GetOwner() const noexcept
		{
			return ::GetWindow(myHandle, GW_OWNER);
		}

		[[nodiscard]]
		inline WindowsHandle GetFirstChild() const noexcept
		{
			return ::GetTopWindow(myHandle);
		}

		[[nodiscard]]
		inline WindowsHandle GetFirstSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDFIRST);
		}

		[[nodiscard]]
		inline WindowsHandle GetLastChild() const noexcept
		{
			return ::GetWindow(myHandle, GW_CHILD);
		}

		[[nodiscard]]
		inline WindowsHandle GetLastSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDLAST);
		}

		[[nodiscard]]
		inline WindowsHandle GetNextSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDNEXT);
		}

		[[nodiscard]]
		inline WindowsHandle GetPrevSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDPREV);
		}

		[[nodiscard]]
		inline WindowsHandle GetWindowParent() const noexcept
		{
			return ::GetParent(myHandle);
		}

		[[nodiscard]]
		inline WindowsHandle GetWindowRoot() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOT);
		}

		[[nodiscard]]
		inline WindowsHandle GetWindowRootOwner() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOTOWNER);
		}

		[[nodiscard]]
		inline const volatile WindowsHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline volatile WindowsHandle&& GetHandle() && noexcept
		{
			return static_cast<volatile WindowsHandle&&>(myHandle);
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

		volatile WindowsHandle myHandle;
		util::atomic_bool isAvailable;
	};

	class [[nodiscard]] ManagedHandle : public DeviceHandle
	{
	protected:
		template<size_t Length>
		explicit constexpr ManagedHandle(const ::HINSTANCE& instance
			, WindowsHandle&& handle
			, _Notnull_ const wchar_t(&class_name)[Length])
			noexcept
			: ManagedHandle(instance, static_cast<WindowsHandle&&>(handle), class_name)
		{}

		explicit constexpr ManagedHandle(const ::HINSTANCE& instance
			, WindowsHandle&& handle
			, _Notnull_ const wchar_t* const& class_name)
			noexcept
			: DeviceHandle(static_cast<WindowsHandle&&>(handle))
			, myInstance(instance)
			, myClassName(class_name)
		{}

	public:
		template<size_t ClassLength, size_t TitleLength>
		[[nodiscard]]
		static ManagedHandle Create(const ::HINSTANCE& instance
			, _Notnull_ const wchar_t(&class_name)[ClassLength]
			, _Notnull_ const wchar_t(&title)[TitleLength]
			, const unsigned int& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
			, const WindowsHandle& parent = NULL
			, const HMENU& menu = nullptr
			, const LPVOID& uparams = nullptr)
			noexcept
		{
			return ManagedHandle
			{
				instance
				, ::CreateWindowEx(0
				, class_name, title
				, style, x, y, width, height
				, parent
				, menu
				, instance, uparams), class_name
			};
		}

		template<size_t ClassLength, size_t TitleLength>
		[[nodiscard]]
		static ManagedHandle Create(const ::HINSTANCE& instance
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
			return Create(instance, class_name, title, style
				, x, y, width, height
				, parent.GetHandle()
				, menu, uparams);
		}

		template<size_t ClassLength, size_t TitleLength>
		[[nodiscard]]
		static ManagedHandle Create(const ::HINSTANCE& instance
			, _Notnull_ const wchar_t(&class_name)[ClassLength]
			, _Notnull_ const wchar_t(&title)[TitleLength]
			, const unsigned int& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
			, const ManagedHandle& parent
			, const HMENU& menu = nullptr
			, const LPVOID& uparams = nullptr)
			noexcept
		{
			return Create(instance, class_name, title, style
				, x, y, width, height
				, parent.GetHandle()
				, menu, uparams);
		}

		virtual ~ManagedHandle() noexcept
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

		[[nodiscard]]
		inline const ::HINSTANCE& GetInstance() const& noexcept
		{
			return myInstance;
		}

		[[nodiscard]]
		inline ::HINSTANCE&& GetInstance() && noexcept
		{
			return static_cast<::HINSTANCE&&>(myInstance);
		}

		ManagedHandle(const ManagedHandle&) = delete;
		constexpr ManagedHandle(ManagedHandle&&) noexcept = default;
		ManagedHandle& operator=(const ManagedHandle&) = delete;
		constexpr ManagedHandle& operator=(ManagedHandle&&) noexcept = default;

		::HINSTANCE myInstance;
		const wchar_t* myClassName;
	};
}
