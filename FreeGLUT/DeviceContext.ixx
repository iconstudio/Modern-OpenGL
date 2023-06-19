module;
#include <Windows.h>
export module Glib.Device.Context;
export import Glib.Device.Handle;

export namespace gl::device
{
	using DeviceContext = ::HDC;
	using GrpContext = ::HGLRC;
	using GrpDescriptor = ::PIXELFORMATDESCRIPTOR;

	class [[nodiscard]] ManagedContext
	{
	public:
		explicit inline ManagedContext(DeviceHandle& hwnd) noexcept
			: myWindow(hwnd)
			, myHandle(::GetDC(hwnd.myHandle))
		{}

		explicit constexpr ManagedContext(DeviceHandle& hwnd, DeviceContext&& handle) noexcept
			: myWindow(hwnd)
			, myHandle(static_cast<DeviceContext&&>(handle))
		{}

		inline ~ManagedContext() noexcept
		{
			::ReleaseDC(myWindow.GetHandle(), myHandle);
		}

		[[nodiscard]]
		inline const DeviceContext& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline DeviceContext&& GetHandle() && noexcept
		{
			return static_cast<DeviceContext&&>(myHandle);
		}

		constexpr ManagedContext(ManagedContext&& other) noexcept
			: myWindow(other.myWindow)
			, myHandle(static_cast<DeviceContext&&>(other.myHandle))
		{}

		constexpr ManagedContext& operator=(ManagedContext&& other) & noexcept
		{
			if (this != &other && myWindow == other.myWindow)
			{
				myHandle = static_cast<DeviceContext&&>(other.myHandle);
			}
			return *this;
		}

		ManagedContext(const ManagedContext&) = delete;
		ManagedContext& operator=(const ManagedContext&) = delete;
		ManagedContext(const ManagedContext&&) = delete;
		ManagedContext& operator=(const ManagedContext&&) = delete;

		DeviceHandle& myWindow;
		DeviceContext myHandle;
	};

	class [[nodiscard]] CompatibleContext
	{
	public:
		inline CompatibleContext(const DeviceContext& ctx) noexcept
			: myHandle(::CreateCompatibleDC(ctx))
		{}

		inline CompatibleContext(DeviceContext&& ctx) noexcept
			: myHandle(::CreateCompatibleDC(static_cast<DeviceContext&&>(ctx)))
		{}

		inline CompatibleContext(const ManagedContext& ctx) noexcept
			: myHandle(::CreateCompatibleDC(ctx.GetHandle()))
		{}

		inline ~CompatibleContext() noexcept
		{
			::DeleteDC(myHandle);
		}

		[[nodiscard]]
		inline const DeviceContext& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline DeviceContext&& GetHandle() && noexcept
		{
			return static_cast<DeviceContext&&>(myHandle);
		}

		CompatibleContext(const CompatibleContext&) = delete;
		CompatibleContext& operator=(const CompatibleContext&) = delete;
		CompatibleContext(CompatibleContext&&) = default;
		CompatibleContext& operator=(CompatibleContext&&) = default;
		CompatibleContext(const CompatibleContext&&) = delete;
		CompatibleContext& operator=(const CompatibleContext&&) = delete;

		DeviceContext myHandle;
	};
}
