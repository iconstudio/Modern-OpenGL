module;
#include "Internal.hpp"

export module Glib.Device.Window:Property;
import Glib.Device.ProcessInstance;
import Utility.Monad;

export namespace gl::device
{
	using ::WNDPROC, ::WNDCLASSEXW;

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

	template<typename T>
	default_property_t(T) -> default_property_t<T>;

	template<typename T>
	inline constexpr default_property_t default_property{};
	inline constexpr int use_default = CW_USEDEFAULT;

	class [[nodiscard]] DeviceProperty
	{
	public:
		constexpr DeviceProperty() noexcept = default;
		constexpr ~DeviceProperty() noexcept = default;

		template<size_t ClassNameSize>
		explicit DeviceProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t(&class_name)[ClassNameSize]
		) noexcept
			: DeviceProperty(hinst, procedure, class_name)
		{}

		explicit DeviceProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t* const& class_name
		) noexcept
			: DeviceProperty(hinst, procedure
						, class_name
						, nullptr //, LoadIconW(hinst, IDI_APPLICATION)
						, nullptr //, LoadIconW(hinst, IDI_APPLICATION)
						, nullptr //, LoadCursorW(hinst, IDC_ARROW)
						, (HBRUSH)(COLOR_WINDOW + 1)
						, nullptr)
		{}

		template<size_t ClassNameSize>
		explicit constexpr DeviceProperty(const HINSTANCE& hinst, WNDPROC procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name
		) noexcept
			: DeviceProperty(hinst, procedure
						, class_name
						, icon
						, small_icon
						, cursor
						, background
						, menu_name)
		{}

		explicit constexpr DeviceProperty(const HINSTANCE& hinst, WNDPROC procedure
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

		util::Monad<WNDCLASSEXW> Register() const noexcept
		{
			if (RegisterClassExW(&myWindowClass))
			{
				return myWindowClass;
			}
			else
			{
				return util::nullopt;
			}
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

		constexpr DeviceProperty(const DeviceProperty&) noexcept = default;
		constexpr DeviceProperty& operator=(const DeviceProperty&) noexcept = default;
		constexpr DeviceProperty(DeviceProperty&&) noexcept = default;
		constexpr DeviceProperty& operator=(DeviceProperty&&) noexcept = default;

	private:
		WNDCLASSEXW myWindowClass;
	};
}
