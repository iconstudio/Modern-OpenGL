module;
#include <Windows.h>
export module Glib.Device.Handle;
export import Glib.Device.ProcessInstance;

export namespace gl::device
{
	using WindowsHandle = ::HWND;

	class [[nodiscard]] DeviceHandle
	{
	protected:
		template<size_t Length>
		constexpr DeviceHandle(const ProcessInstance& instance
			, WindowsHandle&& handle
			, const wchar_t(&class_name)[Length])
			noexcept
			: DeviceHandle(instance, static_cast<WindowsHandle&&>(handle), class_name)
		{}

		constexpr DeviceHandle(const ProcessInstance& instance
			, WindowsHandle&& handle
			, const wchar_t* const& class_name)
			noexcept
			: myInstance(instance)
			, myHandle(static_cast<WindowsHandle&&>(handle))
			, myClassName(class_name)
		{}

	public:
		static DeviceHandle Create(const ProcessInstance& instance
			, const wchar_t* const& class_name
			, const wchar_t* const& title
			, const unsigned int& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
			, const WindowsHandle& parent = nullptr
			, const ::HMENU& menu = nullptr
			, const ::LPVOID& uparams = nullptr)
			noexcept
		{
			return DeviceHandle
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

		virtual ~DeviceHandle() noexcept
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
		inline const WindowsHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline WindowsHandle&& GetHandle() && noexcept
		{
			return static_cast<WindowsHandle&&>(myHandle);
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

		ProcessInstance myInstance;
		WindowsHandle myHandle;
		const wchar_t* myClassName;
	};
}
