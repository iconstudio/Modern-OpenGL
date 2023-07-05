export module Glib.Window;
import <type_traits>;
import <string_view>;
import Glib.Rect;
import Glib.Definitions;
import Glib.Device.IHandle;
import Glib.Device.IWindow;
import Glib.Device.IO;
import Glib.Device.Event;
import Glib.Window.Property;
export import :Style;
export import :Option;

export extern "C++" namespace gl::window
{
	class [[nodiscard]] Window : public device::IHandle<device::IWindow>
	{
	public:
		using base = device::IHandle<device::IWindow>;

		explicit Window(const WindowProperty& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;
		explicit Window(WindowProperty&& properties
			, const std::wstring_view& title
			, const WindowStyle& style
			, const WindowOption& option
			, const int& x
			, const int& y
			, const int& width
			, const int& height
		) noexcept;

		Window(nullptr_t) noexcept;
		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;
		~Window() noexcept;

		void Awake() noexcept;
		void Start() noexcept;
		void UpdateLoop() noexcept;
		bool UpdateOnce() noexcept;
		bool Destroy() noexcept;
		void Swap(Window& other) noexcept;

		bool SendCommand(const device::EventID& msg, const unsigned long long& lhs, const unsigned long& rhs) const noexcept;
		bool SendCommand(const device::EventID& msg) const noexcept;
		bool SendCommand(const device::Event& cmd) const noexcept;
		bool SendCommand(device::Event&& cmd) const noexcept;
		bool SendCommand(const device::EventID& id, const int& keycode, const long long& flags = 0) const noexcept;
		bool SendCommand(const device::EventID& id, const device::io::KeyCode& keycode, const device::io::KeyboardFlag& flags = device::io::KeyboardFlag::None) const noexcept;

		bool Show() noexcept;
		bool Hide() noexcept;
		bool Maximize() noexcept;
		bool Minimize() noexcept;
		bool Restore() noexcept;
		bool Close() noexcept;

		bool Redraw(const bool& flag) noexcept;

		bool EnableInput() noexcept;
		bool DisableInput() noexcept;

		[[nodiscard]] bool IsMinimized() const noexcept;
		[[nodiscard]] bool IsMaximized() const noexcept;
		[[nodiscard]] bool IsRestored() const noexcept;
		[[nodiscard]] bool IsInputEnabled() const noexcept;

		[[nodiscard]] int GetID() const noexcept;
		[[nodiscard]] std::wstring GetTitle() const noexcept;

		[[nodiscard]] WindowStyle GetStyle() const noexcept;
		[[nodiscard]] WindowOption GetOption() const noexcept;
		[[nodiscard]] Rect GetDimensions() const noexcept;
		bool TryGetDimensions(Rect& output) const noexcept;

		long long SetInternalValue(int index, const long long& value) const noexcept;
		long long SetInternalValue(int index, long long&& value) const noexcept;
		long long SetInternalUserData(const long long& value) const noexcept;
		long long SetInternalUserData(long long&& value) const noexcept;
		[[nodiscard]] long long GetInternalValue(int index) const noexcept;
		[[nodiscard]] long long GetInternalUserData() const noexcept;

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

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	protected:
		device::ProcessInstance myInstance;
		WindowProcedure myProcedure;
		const wchar_t* myClassName = nullptr;
	};
}
