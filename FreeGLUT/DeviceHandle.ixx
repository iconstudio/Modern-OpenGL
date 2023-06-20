module;
#include "Internal.hpp"

export module Glib.Device.Handle;
import Utility.Atomic;

export namespace gl::device
{
	using ::HWND, ::HMENU, ::PVOID, ::LPVOID;
	using RawDeviceHandle = ::HWND;

	using ::GetLastError;

	class [[nodiscard]] DeviceHandle
	{
	public:
		constexpr DeviceHandle() noexcept = default;

		constexpr DeviceHandle(nullptr_t) noexcept
			: myHandle(nullptr)
		{}

		constexpr DeviceHandle(RawDeviceHandle&& handle) noexcept
			: myHandle(static_cast<RawDeviceHandle&&>(handle))
		{}

		constexpr DeviceHandle(volatile RawDeviceHandle&& handle) noexcept
			: myHandle(static_cast<volatile RawDeviceHandle&&>(handle))
		{}

		virtual ~DeviceHandle() noexcept
		{
			if (myHandle)
			{
				::DestroyWindow(myHandle);
				myHandle = nullptr;
			}
		}

		constexpr DeviceHandle& operator=(RawDeviceHandle&& handle) noexcept
		{
			myHandle = static_cast<RawDeviceHandle&&>(handle);
			return *this;
		}

		constexpr DeviceHandle& operator=(volatile RawDeviceHandle&& handle) noexcept
		{
			myHandle = static_cast<volatile RawDeviceHandle&&>(handle);
			return *this;
		}

		[[nodiscard]]
		inline const volatile RawDeviceHandle& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline volatile RawDeviceHandle&& GetHandle() && noexcept
		{
			return static_cast<volatile RawDeviceHandle&&>(myHandle);
		}

		constexpr operator RawDeviceHandle() const noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr bool operator==(const DeviceHandle& rhs) const noexcept
		{
			return myHandle == rhs.myHandle;
		}

		DeviceHandle(const DeviceHandle&) = delete;
		constexpr DeviceHandle(DeviceHandle&&) noexcept = default;
		DeviceHandle& operator=(const DeviceHandle&) = delete;
		constexpr DeviceHandle& operator=(DeviceHandle&&) noexcept = default;

		volatile RawDeviceHandle myHandle;
	};

#define IsLButtonDown()  (GetKeyState(VK_LBUTTON) < 0)
#define IsRButtonDown()  (GetKeyState(VK_RBUTTON) < 0)
#define IsMButtonDown()  (GetKeyState(VK_MBUTTON) < 0)
}
