module;
#include "Internal.hpp"

export module Glib.Device.Window;
export import Glib.Device.ProcessInstance;
export import Glib.Device.Context;
export import :Property;
export import :Style;

export namespace gl::device
{
	using ::HWND, ::HMENU, ::PVOID, ::LPVOID;
	using RawDeviceHandle = ::HWND;
	using Message = ::MSG;

	using ::GetLastError;

	class [[nodiscard]] Window
	{
	protected:
		Window(const DeviceProperty& properties)
		{
			const auto& device_class = properties.GetHandle();
			myInstance = device_class.hInstance;

			const DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_ACTIVECAPTION;
			myHandle = DeviceHandle::Create(device_class.hInstance, device_class.lpszClassName, L"title", device_class.style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT);

			if (!myHandle.IsAvailable())
			{
				throw "Failed to create window.";
			}
		}

	public:
		virtual inline ~Window() noexcept
		{
			//::ReleaseDC(myContext, myHandle);
			::UnregisterClass(myClassName, myInstance);
		}

		[[nodiscard]]


		[[nodiscard]]
		constexpr const DeviceHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr DeviceHandle&& GetHandle() && noexcept
		{
			return static_cast<DeviceHandle&&>(myHandle);
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

		constexpr Window(const Window&) noexcept = delete;
		constexpr Window& operator=(const Window&) noexcept = delete;
		constexpr Window(Window&&) noexcept = default;
		constexpr Window& operator=(Window&&) noexcept = default;

		HINSTANCE myInstance;
		DeviceHandle myHandle;
		const wchar_t* myClassName;
	};
}
