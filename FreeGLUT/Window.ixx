export module Glib.Window;
import <type_traits>;
import <string_view>;
import Glib.Rect;
import Glib.DefaultProperty;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Device.Event;
import Glib.Device.IO;
import Glib.Device.Event.API;
import Glib.Window.Property;
import Glib.Device.IWindowHandle;
export import :Style;
export import :Option;

export extern "C++" namespace gl::window
{
	class [[nodiscard]] Window
	{
	public:
		constexpr Window() noexcept = default;

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
			, myProcedure(properties.GetProcedure())
		{
			myHandle = device::MakeNativeWindow(properties.GetInstance().myHandle
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
			, myProcedure(std::move(properties).GetProcedure())
		{
			myHandle = device::MakeNativeWindow(myInstance.myHandle
				, myClassName
				, title
				, Export(style), Export(option)
				, x, y, width, height);
		}

		~Window() noexcept
		{
			if (nullptr != myClassName && nullptr != myHandle.GetHandle())
			{
				device::UnregisterWindow(myInstance.myHandle, myClassName);
			}
		}

		void Awake() noexcept
		{
			Show();
		}

		void Start() noexcept
		{
			myHandle.StartUpdate();
		}

		[[noreturn]]
		void UpdateLoop() noexcept
		{
			while (UpdateOnce())
			{}
		}

		bool UpdateOnce() noexcept
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

		bool SendCommand(const device::EventID& msg, const unsigned long long& lhs, const unsigned long& rhs) const
			noexcept
		{
			return myHandle.SendCommand(msg, lhs, rhs);
		}

		bool SendCommand(const device::EventID& msg) const
			noexcept
		{
			return SendCommand(msg, 0, 0);
		}

		bool SendCommand(const device::Event& cmd) const
			noexcept
		{
			return myHandle.SendCommand(cmd);
		}

		bool SendCommand(device::Event&& cmd) const
			noexcept
		{
			return myHandle.SendCommand(static_cast<device::Event&&>(cmd));
		}

		bool SendCommand(const device::EventID& id, const int& keycode, const long long& flags = 0) const
			noexcept
		{
			return myHandle.SendCommand(id, keycode, flags);
		}

		bool SendCommand(const device::EventID& id, const device::io::KeyCode& keycode, const device::io::KeyboardFlag& flags = device::io::KeyboardFlag::None) const
			noexcept
		{
			return myHandle.SendCommand(id, keycode, flags);
		}

		bool Show() noexcept
		{
			return myHandle.Show();
		}

		bool Hide() noexcept
		{
			return myHandle.Hide();
		}

		bool Maximize() noexcept
		{
			return myHandle.Maximize();
		}

		bool Minimize() noexcept
		{
			return myHandle.Minimize();
		}

		bool Restore() noexcept
		{
			return myHandle.Restore();
		}

		bool Redraw(const bool& flag) noexcept
		{
			return myHandle.Redraw(flag);
		}

		bool EnableInput() noexcept
		{
			return myHandle.EnableInput();
		}

		bool DisableInput() noexcept
		{
			return myHandle.DisableInput();
		}

		bool Close() noexcept
		{
			return myHandle.Close();
		}

		constexpr void Swap(Window& other) noexcept
		{
			std::swap(myHandle, other.myHandle);
			std::swap(myInstance, other.myInstance);
			std::swap(myClassName, other.myClassName);
			std::swap(myProcedure, other.myProcedure);
		}

		[[nodiscard]]
		bool IsMinimized() const noexcept
		{
			return myHandle.IsMinimized();
		}

		[[nodiscard]]
		bool IsMaximized() const noexcept
		{
			return myHandle.IsMaximized();
		}

		[[nodiscard]]
		bool IsRestored() const noexcept
		{
			return myHandle.IsRestored();
		}

		[[nodiscard]]
		bool IsInputEnabled() const noexcept
		{
			return myHandle.IsInputEnabled();
		}

		inline long long SetInternalValue(int index, const long long& value) const noexcept
		{
			return myHandle.SetInternalValue(index, value);
		}

		inline long long SetInternalValue(int index, long long&& value) const noexcept
		{
			return myHandle.SetInternalValue(index, std::move(value));
		}

		inline long long SetInternalUserData(const long long& value) const noexcept
		{
			return myHandle.SetInternalUserData(value);
		}

		inline long long SetInternalUserData(long long&& value) const noexcept
		{
			return myHandle.SetInternalUserData(std::move(value));
		}

		[[nodiscard]]
		inline long long GetInternalValue(int index) const noexcept
		{
			return myHandle.GetInternalValue(index);
		}

		[[nodiscard]]
		inline long long GetInternalUserData() const noexcept
		{
			return myHandle.GetInternalUserData();
		}

		[[nodiscard]]
		WindowStyle GetStyle() const noexcept
		{
			return WindowStyle{ myHandle.GetStyle() };
		}

		/// <summary>
		/// GetExStyle
		/// </summary>
		[[nodiscard]]
		WindowOption GetOption() const noexcept
		{
			return WindowOption{ myHandle.GetExStyle() };
		}

		[[nodiscard]]
		int GetID() const noexcept
		{
			return myHandle.GetID();
		}

		[[nodiscard]]
		Rect GetDimensions() const noexcept
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
		bool TryGetDimensions(Rect& output) const noexcept
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
			, myProcedure(std::exchange(other.myProcedure, nullptr))
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
		WindowProcedure myProcedure = nullptr;
		const wchar_t* myClassName = nullptr;
	};
}
