module;
#include "Internal.hpp"

export module Glib.Window.Property;
import <type_traits>;
import Glib.Device.ProcessInstance;

export extern "C++" namespace gl::window
{
	//using ::WNDPROC;
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);
	using RawWindowProperty = ::tagWNDCLASSEXW;

	inline constexpr RawWindowProperty DefaultWindowProperty = 
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
}
