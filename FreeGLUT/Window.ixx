module;
export module Glib.Device.Window;
import <string_view>;
export import Glib.Rect;
export import Glib.DefaultProperty;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Context;
export import Glib.Device.Handle;
export import :Property;
export import :Style;
export import :Option;
export import :ABI;

export extern "C++" namespace gl::device
{
	class [[nodiscard]] Window
	{
	protected:
		Window(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
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
				, Export(style), Export(option)
				, x, y, width, height);
		}

		Window(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept
			: myInstance(static_cast<WindowProperty&&>(properties).GetInstance())
			, myClassName(static_cast<WindowProperty&&>(properties).GetClass())
			, myHandle(nullptr)
		{
			myHandle = detail::CreateNativeWindow(myInstance
				, myClassName
				, title
				, Export(style), Export(option)
				, x, y, width, height);
		}

	public:
		[[nodiscard]]
		friend Window CreateWindow(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		[[nodiscard]]
		inline friend Window CreateWindow(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const Rect& dimension
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const Rect& dimension
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		[[nodiscard]]
		inline friend Window CreateWindow(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const Rect& dimension
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const Rect& dimension
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(const WindowProperty& properties
			, const std::wstring_view& title
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		[[nodiscard]]
		inline friend Window CreateWindow(WindowProperty&& properties
			, const std::wstring_view& title
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(const WindowProperty& properties
			, const std::wstring_view& title
			, const Rect& dimension
		) noexcept;

		[[nodiscard]]
		friend Window CreateWindow(WindowProperty&& properties
			, const std::wstring_view& title
			, const Rect& dimension
		) noexcept;

		constexpr Window() noexcept = default;

		virtual inline ~Window() noexcept
		{
			detail::UnregisterProcess(myInstance, myClassName);
		}

		inline void Awake() noexcept
		{
			Show();
		}

		inline void Start() noexcept
		{
			myHandle.StartUpdate();
		}

		inline bool SendCommand(const unsigned int& msg, const WPARAM& lhs, const LPARAM& rhs) const
			noexcept
		{
			return myHandle.SendCommand(msg, lhs, rhs);
		}

		inline bool SendCommand(const unsigned int& msg) const
			noexcept
		{
			return SendCommand(msg, 0, 0);
		}

		inline bool SetWindowRedraw(const bool& flag) noexcept
		{
			return myHandle.SetWindowRedraw(flag);
		}

		inline bool UICommand(const int& cmd) noexcept
		{
			return myHandle.UICommand(cmd);
		}

		inline bool Close() noexcept
		{
			return myHandle.Close();
		}

		inline bool Show() noexcept
		{
			return myHandle.Show();
		}

		inline bool Hide() noexcept
		{
			return myHandle.Hide();
		}

		inline bool Maximize() noexcept
		{
			return myHandle.Maximize();
		}

		inline bool Minimize() noexcept
		{
			return myHandle.Minimize();
		}

		inline bool Restore() noexcept
		{
			return myHandle.Restore();
		}

		inline bool MakeFocus() noexcept
		{
			return myHandle.MakeFocus();
		}

		inline bool MakeForeground() noexcept
		{
			return myHandle.MakeForeground();
		}

		[[nodiscard]]
		inline bool IsMinimized() const noexcept
		{
			return myHandle.IsMinimized();
		}

		[[nodiscard]]
		inline bool IsMaximized() const noexcept
		{
			return myHandle.IsMaximized();
		}

		[[nodiscard]]
		inline bool IsRestored() const noexcept
		{
			return myHandle.IsRestored();
		}

		[[nodiscard]]
		inline DWORD GetStyle() const noexcept
		{
			return myHandle.GetStyle();
		}

		[[nodiscard]]
		inline DWORD GetExStyle() const noexcept
		{
			return myHandle.GetExStyle();
		}

		[[nodiscard]]
		inline int GetID() const noexcept
		{
			return myHandle.GetID();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetOwner() const noexcept
		{
			return myHandle.GetOwner();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetFirstChild() const noexcept
		{
			return myHandle.GetFirstChild();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetFirstSibling() const noexcept
		{
			return myHandle.GetFirstSibling();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetLastChild() const noexcept
		{
			return myHandle.GetLastChild();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetLastSibling() const noexcept
		{
			return myHandle.GetLastSibling();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetNextSibling() const noexcept
		{
			return myHandle.GetNextSibling();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetPrevSibling() const noexcept
		{
			return myHandle.GetPrevSibling();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetParent() const noexcept
		{
			return myHandle.GetParent();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetRoot() const noexcept
		{
			return myHandle.GetRoot();
		}

		[[nodiscard]]
		inline RawDeviceHandle GetRootOwner() const noexcept
		{
			return myHandle.GetRootOwner();
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

		ProcessInstance myInstance;
		DeviceHandle myHandle;
		const wchar_t* myClassName;
	};

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ properties, title, style, option, x, y, width, height };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, option, x, y, width, height };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const Rect& dimension) noexcept
	{
		return Window{ properties, title, style, option, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const Rect& dimension) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, option, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	inline Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return Window{ properties, title, style, options::Default, x, y, width, height };
	}

	inline Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, options::Default, x, y, width, height };
	}

	inline Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept
	{
		return Window{ properties, title, style, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	inline Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ properties, title, styles::Default, options::Default, x, y, width, height };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, styles::Default, options::Default, x, y, width, height };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const Rect& dimension) noexcept
	{
		return Window{ properties, title, styles::Default, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const Rect& dimension) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, styles::Default, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}
}
