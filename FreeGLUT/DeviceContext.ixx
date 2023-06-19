module;
#include "Internal.hpp"

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

		explicit constexpr ManagedContext(DeviceHandle& hwnd, ::HDC&& handle) noexcept
			: myWindow(hwnd)
			, myHandle(static_cast<::HDC&&>(handle))
		{}

		inline ~ManagedContext() noexcept
		{
			::ReleaseDC(myWindow.GetHandle(), myHandle);
		}

		[[nodiscard]]
		inline const ::HDC& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline ::HDC&& GetHandle() && noexcept
		{
			return static_cast<::HDC&&>(myHandle);
		}

		constexpr ManagedContext(ManagedContext&& other) noexcept
			: myWindow(other.myWindow)
			, myHandle(static_cast<::HDC&&>(other.myHandle))
		{}

		constexpr ManagedContext& operator=(ManagedContext&& other) & noexcept
		{
			if (this != &other && myWindow == other.myWindow)
			{
				myHandle = static_cast<::HDC&&>(other.myHandle);
			}
			return *this;
		}

		ManagedContext(const ManagedContext&) = delete;
		ManagedContext& operator=(const ManagedContext&) = delete;
		ManagedContext(const ManagedContext&&) = delete;
		ManagedContext& operator=(const ManagedContext&&) = delete;

		DeviceHandle& myWindow;
		::HDC myHandle;
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

		virtual inline ~CompatibleContext() noexcept
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
