module;
#include "Internal.hpp"

export module Glib.Device.Context;
export import Glib.Device.Handle;

export namespace gl::device
{
	using RawDeviceContext = ::HDC;
	using GrpContext = ::HGLRC;
	using GrpDescriptor = ::PIXELFORMATDESCRIPTOR;

	class [[nodiscard]] DeviceContext
	{
	public:
		explicit inline DeviceContext(DeviceHandle& hwnd) noexcept
			: myHandle(::GetDC(hwnd.GetHandle()))
		{}

		explicit constexpr DeviceContext(RawDeviceContext&& handle) noexcept
			: myHandle(static_cast<RawDeviceContext&&>(handle))
		{}

		inline ~DeviceContext() noexcept
		{
			::ReleaseDC(nullptr, myHandle);
		}

		[[nodiscard]]
		inline const RawDeviceContext& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline RawDeviceContext&& GetHandle() && noexcept
		{
			return static_cast<RawDeviceContext&&>(myHandle);
		}

		DeviceContext(const DeviceContext&) = delete;
		constexpr DeviceContext(DeviceContext&& other) noexcept = default;
		DeviceContext& operator=(const DeviceContext&) = delete;
		constexpr DeviceContext& operator=(DeviceContext&& other) noexcept = default;

		RawDeviceContext myHandle;
	};

	class [[nodiscard]] CompatibleContext
	{
	public:
		inline CompatibleContext(const RawDeviceContext& ctx) noexcept
			: myHandle(::CreateCompatibleDC(ctx))
		{}

		inline CompatibleContext(RawDeviceContext&& ctx) noexcept
			: myHandle(::CreateCompatibleDC(static_cast<RawDeviceContext&&>(ctx)))
		{}

		inline CompatibleContext(const DeviceContext& ctx) noexcept
			: myHandle(::CreateCompatibleDC(ctx.GetHandle()))
		{}

		virtual inline ~CompatibleContext() noexcept
		{
			::DeleteDC(myHandle);
		}

		[[nodiscard]]
		inline const RawDeviceContext& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		inline RawDeviceContext&& GetHandle() && noexcept
		{
			return static_cast<RawDeviceContext&&>(myHandle);
		}

		CompatibleContext(const CompatibleContext&) = delete;
		CompatibleContext& operator=(const CompatibleContext&) = delete;
		CompatibleContext(CompatibleContext&&) = default;
		CompatibleContext& operator=(CompatibleContext&&) = default;
		CompatibleContext(const CompatibleContext&&) = delete;
		CompatibleContext& operator=(const CompatibleContext&&) = delete;

		RawDeviceContext myHandle;
	};
}
