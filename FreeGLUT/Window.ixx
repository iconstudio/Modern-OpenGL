module;
#include "Internal.hpp"

export module Glib.Device.Window;
import <string_view>;
export import Glib.Rect;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Context;
export import Glib.Device.Handle;
export import :Property;
export import :Style;
export import :ABI;

export namespace gl::device
{
	using Message = ::MSG;

	using ::GetLastError;

	template<typename T>
	struct [[nodiscard]] default_property_t;

	template<typename T>
	struct [[nodiscard]] default_property_t
	{
		constexpr default_property_t() noexcept = default;
		constexpr ~default_property_t() noexcept = default;

		template<typename U>
		constexpr default_property_t(U&& pass) noexcept
			: value(static_cast<U&&>(pass))
		{}

		constexpr operator T& () & noexcept
		{
			return value;
		}

		constexpr operator T const& () const& noexcept
		{
			return value;
		}

		constexpr operator T && () && noexcept
		{
			return static_cast<T&&>(value);
		}

		constexpr operator T const&& () const&& noexcept
		{
			return static_cast<T&&>(value);
		}

		[[nodiscard]]
		constexpr bool operator==(const default_property_t& rhs) const
		{
			if (this == &rhs)
			{
				return true;
			}

			return false;
		}

		constexpr default_property_t(const default_property_t&) noexcept = default;
		constexpr default_property_t& operator=(const default_property_t&) noexcept = default;
		constexpr default_property_t(default_property_t&&) noexcept = default;
		constexpr default_property_t& operator=(default_property_t&&) noexcept = default;

		T value;
	};

	template<>
	struct [[nodiscard]] default_property_t<void>
	{
		constexpr default_property_t() noexcept = default;
		constexpr ~default_property_t() noexcept = default;
	};

	template<typename T>
	default_property_t(T) -> default_property_t<T>;

	template<typename T>
	inline constexpr default_property_t default_property{};
	inline constexpr default_property_t use_default = default_property_t{ CW_USEDEFAULT };

	class [[nodiscard]] Window
	{
	protected:
		Window(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept
			: myInstance(properties.GetInstance())
			, myClassName(properties.GetClass())
			, myHandle(nullptr)
		{
			myHandle = detail::CreateNativeWindow(properties.GetInstance()
				, properties.GetClass()
				, title
				, Export(style), 0
				, x, y, width, height);
		}

	public:
		[[nodiscard]]
		static inline Window Create(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept
		{
			return Window{ properties, title, style, x, y, width, height };
		}

		[[nodiscard]]
		static inline Window Create(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept
		{
			return Window{ static_cast<WindowProperty&&>(properties), title, style, x, y, width, height };
		}

		[[nodiscard]]
		static inline Window Create(const WindowProperty& properties
			, const std::wstring_view& title
			, WindowStyle&& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept
		{
			return Window{ properties, title, static_cast<WindowStyle&&>(style), x, y, width, height };
		}

		[[nodiscard]]
		static inline Window Create(WindowProperty&& properties
			, const std::wstring_view& title
			, WindowStyle&& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept
		{
			return Window{ static_cast<WindowProperty&&>(properties), title, static_cast<WindowStyle&&>(style), x, y, width, height };
		}

		[[nodiscard]]
		static inline Window Create(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const Rect& dimension
		) noexcept
		{
			return Window{ properties, title, style, dimension.x, dimension.y, dimension.w, dimension.h };
		}

		[[nodiscard]]
		static inline Window Create(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const Rect& dimension
		) noexcept
		{
			return Window{ static_cast<WindowProperty&&>(properties), title, style, dimension.x, dimension.y, dimension.w, dimension.h };
		}

		[[nodiscard]]
		static inline Window Create(WindowProperty&& properties
			, const std::wstring_view& title
			, WindowStyle&& style
			, const Rect& dimension
		) noexcept
		{
			return Window{ static_cast<WindowProperty&&>(properties), title, static_cast<WindowStyle&&>(style), dimension.x, dimension.y, dimension.w, dimension.h };
		}

		constexpr Window() noexcept = default;

		virtual inline ~Window() noexcept
		{
			::UnregisterClass(myClassName, myInstance);
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

		inline bool UICommand(const int& cmd) noexcept
		{
			return SendCommand(WM_SHOWWINDOW, static_cast<WPARAM>(cmd), 0);
		}

		inline bool Close() noexcept
		{
			return SendCommand(WM_CLOSE);
		}

		inline bool Show() noexcept
		{
			return 0 != ::ShowWindow(myHandle, SW_SHOW);
		}

		inline bool Hide() noexcept
		{
			return 0 != ::ShowWindow(myHandle, SW_HIDE);
		}

		inline bool Maximize() noexcept
		{
			return UICommand(SW_MAXIMIZE);
		}

		inline bool Minimize() noexcept
		{
			return UICommand(SW_MINIMIZE);
		}

		inline bool Restore() noexcept
		{
			return UICommand(SW_RESTORE);
		}

		inline bool MakeFocus() noexcept
		{
			return UICommand(WM_SETFOCUS);
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
		inline HWND GetOwner() const noexcept
		{
			return ::GetWindow(myHandle, GW_OWNER);
		}

		[[nodiscard]]
		inline HWND GetFirstChild() const noexcept
		{
			return ::GetTopWindow(myHandle);
		}

		[[nodiscard]]
		inline HWND GetFirstSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDFIRST);
		}

		[[nodiscard]]
		inline HWND GetLastChild() const noexcept
		{
			return ::GetWindow(myHandle, GW_CHILD);
		}

		[[nodiscard]]
		inline HWND GetLastSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDLAST);
		}

		[[nodiscard]]
		inline HWND GetNextSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDNEXT);
		}

		[[nodiscard]]
		inline HWND GetPrevSibling() const noexcept
		{
			return ::GetWindow(myHandle, GW_HWNDPREV);
		}

		[[nodiscard]]
		inline HWND GetParent() const noexcept
		{
			return ::GetParent(myHandle);
		}

		[[nodiscard]]
		inline HWND GetRoot() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOT);
		}

		[[nodiscard]]
		inline HWND GetRootOwner() const noexcept
		{
			return ::GetAncestor(myHandle, GA_ROOTOWNER);
		}

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

		Window(const Window&) = delete;
		constexpr Window(Window&&) noexcept = default;
		Window& operator=(const Window&) = delete;
		constexpr Window& operator=(Window&&) noexcept = default;

		HINSTANCE myInstance;
		DeviceHandle myHandle;
		const wchar_t* myClassName;
	};
}
