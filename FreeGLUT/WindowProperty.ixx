module;
#include "Internal.hpp"

export module Glib.Window.Property;
import <type_traits>;
import Glib.Device.ProcessInstance;
import Glib.Device.Brush;
import Glib.Device.Brush.Component;
import Glib.Device.Resource.Icon;

export extern "C++" namespace gl::window
{
	//using ::WNDPROC;
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);
	using RawWindowProperty = ::tagWNDCLASSEXW;

	inline constexpr RawWindowProperty DefaultWindowProperty
	{
		.cbSize = sizeof(RawWindowProperty),
			.style = CS_HREDRAW | CS_VREDRAW,
			.lpfnWndProc = nullptr,
			.cbClsExtra = 0,
			.cbWndExtra = sizeof(void*),
			.hInstance = nullptr,
			.hIcon = nullptr,
			.hCursor = nullptr,
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = nullptr,
			.hIconSm = nullptr,
	};

	class [[nodiscard]] WindowProperty
	{
	public:
		constexpr WindowProperty() noexcept = default;
		constexpr ~WindowProperty() noexcept = default;

		explicit constexpr WindowProperty(const RawWindowProperty& data) noexcept
			: myWindowClass(data)
		{}

		explicit constexpr WindowProperty(RawWindowProperty&& data) noexcept
			: myWindowClass(std::move(data))
		{}

		inline bool Register() noexcept
		{
			return 0 == ::RegisterClassEx(std::addressof(myWindowClass));
		}

		inline bool Deregister() noexcept
		{
			return FALSE != ::UnregisterClass(myWindowClass.lpszClassName, myWindowClass.hInstance);
		}

		[[nodiscard]]
		constexpr const RawWindowProperty& GetHandle() const& noexcept
		{
			return myWindowClass;
		}

		[[nodiscard]]
		constexpr RawWindowProperty&& GetHandle() && noexcept
		{
			return static_cast<RawWindowProperty&&>(myWindowClass);
		}

		[[nodiscard]]
		constexpr device::ProcessInstance GetInstance() const& noexcept
		{
			return device::ProcessInstance{ myWindowClass.hInstance };
		}

		[[nodiscard]]
		constexpr device::ProcessInstance GetInstance() && noexcept
		{
			return device::ProcessInstance{ static_cast<device::HINSTANCE&&>(myWindowClass.hInstance) };
		}

		[[nodiscard]]
		constexpr const WindowProcedure& GetProcedure() const& noexcept
		{
			return myWindowClass.lpfnWndProc;
		}

		[[nodiscard]]
		constexpr WindowProcedure&& GetProcedure() && noexcept
		{
			return static_cast<WindowProcedure&&>(myWindowClass.lpfnWndProc);
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

		RawWindowProperty myWindowClass{};
	};

	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, const device::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = background.GetHandle(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, device::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = std::move(background).GetHandle(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	template<device::ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = device::GetComponentColouring<BkColorReference>(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon = nullptr
		, device::resource::Icon&& small_icon = nullptr
		, device::resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = device::MakeDefaultComponentColouring(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}
}
