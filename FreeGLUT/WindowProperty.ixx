module;
#include "Internal.hpp"

export module Glib.Device.Window:Property;
import Utility.Monad;

export namespace gl::device
{
	using Procedure = ::WNDPROC;
	using RawDeviceClass = ::WNDCLASSEXW;

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

		constexpr operator T&& () && noexcept
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

		template<size_t ClassNameSize, size_t MenuNameSize>
		explicit DeviceProperty(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
		) noexcept
			: DeviceProperty(handle, procedure
						, class_name
						, LoadIconW(handle, IDI_APPLICATION)
						, LoadIconW(handle, IDI_APPLICATION)
						, LoadCursorW(handle, IDC_ARROW)
						, (HBRUSH)(COLOR_WINDOW + 1)
						, nullptr)
		{}

		template<size_t ClassNameSize, size_t MenuNameSize>
		explicit constexpr DeviceProperty(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t(&menu_name)[MenuNameSize]
		) noexcept
			: DeviceProperty(handle, procedure
						, class_name
						, icon
						, small_icon
						, cursor
						, background
						, menu_name)
		{}


		template<size_t ClassNameSize, size_t MenuNameSize>
		explicit constexpr DeviceProperty(HINSTANCE handle, Procedure procedure
			, const wchar_t(&class_name)[ClassNameSize]
			, const ::HICON& icon
			, const ::HICON& small_icon
			, const ::HCURSOR& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name) noexcept
		{
			myWindowClass.cbSize = sizeof(WNDCLASSEXW);
			myWindowClass.hInstance = handle;
			myWindowClass.lpszClassName = class_name;
			myWindowClass.lpfnWndProc = procedure;
			myWindowClass.cbClsExtra = 0;
			myWindowClass.cbWndExtra = 0;
			myWindowClass.style = CS_HREDRAW | CS_VREDRAW;
			myWindowClass.hbrBackground = background;
			myWindowClass.lpszMenuName = menu_name;
			myWindowClass.hIcon = icon;
			myWindowClass.hIconSm = small_icon;
			myWindowClass.hCursor = cursor;
		}

		util::Monad<RawDeviceClass> Register() const noexcept
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
		constexpr const RawDeviceClass& GetHandle() const& noexcept
		{
			return myWindowClass;
		}

		[[nodiscard]]
		constexpr RawDeviceClass&& GetHandle() && noexcept
		{
			return static_cast<RawDeviceClass&&>(myWindowClass);
		}

		constexpr DeviceProperty(const DeviceProperty&) noexcept = default;
		constexpr DeviceProperty& operator=(const DeviceProperty&) noexcept = default;
		constexpr DeviceProperty(DeviceProperty&&) noexcept = default;
		constexpr DeviceProperty& operator=(DeviceProperty&&) noexcept = default;

	private:
		RawDeviceClass myWindowClass;
	};
}
