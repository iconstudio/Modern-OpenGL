module;
#include "Internal.hpp"

export module Glib.Device.Window:Property;
import Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ::WNDPROC, ::WNDCLASSEXW;

	class [[nodiscard]] WindowProperty
	{
	public:
		constexpr WindowProperty() noexcept = default;
		constexpr ~WindowProperty() noexcept = default;

		template<size_t ClassNameSize>
		explicit WindowProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t(&class_name)[ClassNameSize]
		) noexcept
			: WindowProperty(hinst, procedure, class_name)
		{}

		explicit WindowProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t* const& class_name
		) noexcept
			: WindowProperty(hinst, procedure
						, class_name
						, nullptr //, LoadIconW(hinst, IDI_APPLICATION)
						, nullptr //, LoadIconW(hinst, IDI_APPLICATION)
						, nullptr //, LoadCursorW(hinst, IDC_ARROW)
						, (HBRUSH)(COLOR_WINDOW + 1)
						, nullptr)
		{}

		template<size_t ClassNameSize>
		explicit constexpr WindowProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name
		) noexcept
			: WindowProperty(hinst, procedure
						, class_name
						, icon
						, small_icon
						, cursor
						, background
						, menu_name)
		{}

		explicit constexpr WindowProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t* const& class_name
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name
		) noexcept
			: myWindowClass()
		{
			myWindowClass.cbSize = sizeof(WNDCLASSEXW);
			myWindowClass.hInstance = hinst;
			myWindowClass.lpszClassName = class_name;
			myWindowClass.lpfnWndProc = procedure;
			myWindowClass.cbClsExtra = 0;
			myWindowClass.cbWndExtra = 0;
			myWindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			myWindowClass.hbrBackground = background;
			myWindowClass.lpszMenuName = menu_name;
			myWindowClass.hIcon = icon;
			myWindowClass.hIconSm = small_icon;
			myWindowClass.hCursor = cursor;
		}

		inline bool Register() noexcept
		{
			return 0 == RegisterClassExW(&myWindowClass);
		}

		[[nodiscard]]
		constexpr const WNDCLASSEXW& GetHandle() const& noexcept
		{
			return myWindowClass;
		}

		[[nodiscard]]
		constexpr WNDCLASSEXW&& GetHandle() && noexcept
		{
			return static_cast<WNDCLASSEXW&&>(myWindowClass);
		}

		[[nodiscard]]
		constexpr const HINSTANCE& GetInstance() const& noexcept
		{
			return myWindowClass.hInstance;
		}

		[[nodiscard]]
		constexpr ::HINSTANCE&& GetInstance() && noexcept
		{
			return static_cast<HINSTANCE&&>(myWindowClass.hInstance);
		}

		[[nodiscard]]
		constexpr const wchar_t* const& GetClass() const& noexcept
		{
			return myWindowClass.lpszClassName;
		}

		[[nodiscard]]
		constexpr const wchar_t*&& GetClass() && noexcept
		{
			return static_cast<const wchar_t*&&>(myWindowClass.lpszClassName);
		}

		constexpr WindowProperty(const WindowProperty&) noexcept = default;
		constexpr WindowProperty& operator=(const WindowProperty&) noexcept = default;
		constexpr WindowProperty(WindowProperty&&) noexcept = default;
		constexpr WindowProperty& operator=(WindowProperty&&) noexcept = default;

	private:
		WNDCLASSEXW myWindowClass;
	};
}
