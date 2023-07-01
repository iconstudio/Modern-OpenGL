export module Glib.Window;
import <type_traits>;
import <string_view>;
import Utility.Concurrency.Thread;
export import Glib.Rect;
import Glib.DefaultProperty;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Device.Event;
import Glib.Device.IO;
import Glib.Device.Event.API;
import Glib.Window.Property;
export import :Style;
export import :Option;
export import :ABI;

export extern "C++" namespace gl::window
{
	class [[nodiscard]] Window
	{
	public:
		explicit Window(const WindowProperty& properties
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

		explicit Window(WindowProperty&& properties
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

		inline bool Close() noexcept
		{
			return myHandle.Close();
		}

		constexpr void Swap(Window& other) noexcept
		{
			std::swap(myHandle, other.myHandle);
			std::swap(myInstance, other.myInstance);
			std::swap(myClassName, other.myClassName);
			std::swap(myProcecure, other.myProcecure);
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
		constexpr const wchar_t* const& GetClassName() const& noexcept
		{
			return myClassName;
		}

		[[nodiscard]]
		constexpr const wchar_t*&& GetClassName() && noexcept
		{
			return static_cast<const wchar_t*&&>(myClassName);
		}

		constexpr Window(Window&& other) noexcept
			: myInstance(std::exchange(other.myInstance, nullptr))
			, myHandle(std::exchange(other.myHandle, nullptr))
			, myProcecure(std::exchange(other.myProcecure, nullptr))
			, myClassName(std::exchange(other.myClassName, nullptr))
		{}

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
	};

	using device::PostQuitMessage;
}
