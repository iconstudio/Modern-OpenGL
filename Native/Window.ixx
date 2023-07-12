export module Glib.Windows.Client;
import <type_traits>;
import <string_view>;
import Glib.Rect;
import Glib.Windows.Definitions;
import Glib.Windows.IWindow;
import Glib.Windows.IO;
import Glib.Windows.Event;
import Glib.Windows.Client.Property;
export import :Style;
export import :Option;

export namespace gl::win32
{
	class [[nodiscard]] Window : public IWindow
	{
	public:
		using base = IWindow;

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
		bool UpdateOnce() noexcept;
		void Swap(Window& other) noexcept;

		[[nodiscard]] WindowStyle GetStyle() const noexcept;
		[[nodiscard]] WindowOption GetOption() const noexcept;

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
		ProcessInstance myInstance;
		WindowProcedure myProcedure;
		const wchar_t* myClassName = nullptr;

	private:
		using base::StartUpdate;
		using base::GetStyle;
		using base::GetExStyle;
	};
}
