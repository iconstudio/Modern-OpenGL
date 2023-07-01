module;
export module Glib.Window;
import <string_view>;
import Utility.Concurrency.Thread;
export import Glib.Rect;
export import Glib.DefaultProperty;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Context;
export import Glib.Device.Handle;
export import Glib.Device.Event;
export import Glib.Device.IO;
import Glib.Device.Event.API;
export import :Property;
export import :Style;
export import :Option;
export import :ABI;

export extern "C++" namespace gl::window
{
	class [[nodiscard]] Window
	{
	public:
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
			, myProcecure(properties.GetProcedure())
		{
			myHandle = detail::CreateNativeWindow(properties.GetInstance().myHandle
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
			: myInstance(std::move(properties).GetInstance())
			, myClassName(std::move(properties).GetClass())
			, myProcecure(std::move(properties).GetProcedure())
		{
			myHandle = detail::CreateNativeWindow(myInstance.myHandle
				, myClassName
				, title
				, Export(style), Export(option)
				, x, y, width, height);
		}

		Window() noexcept = default;

		inline ~Window() noexcept
		{
			if (nullptr != myClassName && nullptr != myHandle.GetHandle())
			{
				device::UnregisterWindow(myInstance.myHandle, myClassName);
			}
		}

		inline void Awake() noexcept
		{
			Show();
		}

		inline void Start() noexcept
		{
			myHandle.StartUpdate();
		}

		[[noreturn]]
		inline void UpdateLoop(util::stop_token canceller) noexcept
		{
			while (UpdateOnce())
			{
				if (canceller.stop_requested())
					break;
			}
		}

		inline bool UpdateOnce() noexcept
		{
			device::RawEvent event = device::EventAPI::MakeEvent();

			if (device::EventAPI::Pop(myHandle, event))
			{
				if (!device::EventAPI::Translate(event))
				{
				}

				device::EventAPI::Dispatch(event);
				return true;
			}

			return false;
		}

		inline bool SendCommand(const unsigned int& msg, const unsigned long long& lhs, const unsigned long& rhs) const
			noexcept
		{
			return myHandle.SendCommand(msg, lhs, rhs);
		}

		inline bool SendCommand(const unsigned int& msg) const
			noexcept
		{
			return SendCommand(msg, 0, 0);
		}

		inline bool SendCommand(const device::EventID& msg, const unsigned long long& lhs, const unsigned long& rhs) const
			noexcept
		{
			return myHandle.SendCommand(msg, lhs, rhs);
		}

		inline bool SendCommand(const device::EventID& msg) const
			noexcept
		{
			return SendCommand(msg, 0, 0);
		}

		inline bool SendCommand(const device::Event& cmd) const
			noexcept
		{
			return myHandle.SendCommand(cmd);
		}

		inline bool SendCommand(device::Event&& cmd) const
			noexcept
		{
			return myHandle.SendCommand(static_cast<device::Event&&>(cmd));
		}

		inline bool SendCommand(const device::EventID& id, const int& keycode, const long long& flags = 0) const
			noexcept
		{
			return myHandle.SendCommand(id, keycode, flags);
		}

		inline bool SendCommand(const device::EventID& id, const device::io::KeyCode& keycode, const device::io::KeyboardFlag& flags = device::io::KeyboardFlag::None) const
			noexcept
		{
			return myHandle.SendCommand(id, keycode, flags);
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

		inline bool Redraw(const bool& flag) noexcept
		{
			return myHandle.Redraw(flag);
		}

		inline bool EnableInput() noexcept
		{
			return myHandle.EnableInput();
		}

		inline bool DisableInput() noexcept
		{
			return myHandle.DisableInput();
		}

		constexpr void Swap(Window& other) noexcept
		{
			std::swap(myHandle, other.myHandle);
			std::swap(myInstance, other.myInstance);
			std::swap(myClassName, other.myClassName);
			std::swap(myProcecure, other.myProcecure);
			std::swap(frameLimit, other.frameLimit);
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
		inline bool IsInputEnabled() const noexcept
		{
			return myHandle.IsInputEnabled();
		}

		[[nodiscard]]
		inline WindowStyle GetStyle() const noexcept
		{
			return WindowStyle{ myHandle.GetStyle() };
		}

		/// <summary>
		/// GetExStyle
		/// </summary>
		[[nodiscard]]
		inline WindowOption GetOption() const noexcept
		{
			return WindowOption{ myHandle.GetExStyle() };
		}

		[[nodiscard]]
		inline int GetID() const noexcept
		{
			return myHandle.GetID();
		}

		[[nodiscard]]
		inline Rect GetDimensions() const noexcept
		{
			auto result = myHandle.GetDimensions();
			return Rect
			{
				result.left,
				result.top,
				result.right - result.left,
				result.bottom - result.top
			};
		}

		[[nodiscard]]
		inline bool TryGetDimensions(Rect& output) const noexcept
		{
			auto result = device::MakeNativeRect();
			const bool ok = myHandle.TryGetDimensions(result);
			if (ok)
			{
				output = Rect
				{
					result.left, result.top, result.right - result.left, result.bottom - result.top
				};
			}

			return ok;
		}

		[[nodiscard]]
		constexpr const device::DeviceHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr device::DeviceHandle&& GetHandle() && noexcept
		{
			return static_cast<device::DeviceHandle&&>(myHandle);
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

		constexpr Window(Window&& other) noexcept
			: myInstance(static_cast<device::ProcessInstance&&>(other.myInstance))
			, myHandle(static_cast<device::DeviceHandle&&>(other.myHandle))
			, myProcecure(static_cast<WindowProcedure&&>(other.myProcecure))
			, myClassName(static_cast<const wchar_t*&&>(other.myClassName))
		{
			other.myInstance = nullptr;
			other.myHandle = nullptr;
			other.myProcecure = nullptr;
			other.myClassName = nullptr;
			other.frameLimit = 0;
		}

		constexpr Window& operator=(Window&& other) noexcept
		{
			other.Swap(*this);
			return *this;
		}

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		device::ProcessInstance myInstance = nullptr;
		device::DeviceHandle myHandle = nullptr;
		WindowProcedure myProcecure = nullptr;
		const wchar_t* myClassName = nullptr;

		bool isFrameLimited = false;
		unsigned int frameLimit = 0;
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

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, Rect&& dimension) noexcept
	{
		return Window
		{
			properties
			, title
			, styles::Default , options::Default
			, std::move(dimension.x), std::move(dimension.y)
			, std::move(dimension.w), std::move(dimension.h)
		};
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, Rect&& dimension) noexcept
	{
		return Window
		{
			std::move(properties)
			, title
			, styles::Default , options::Default
			, std::move(dimension.x), std::move(dimension.y)
			, std::move(dimension.w), std::move(dimension.h)
		};
	}

	using device::PostQuitMessage;
}
