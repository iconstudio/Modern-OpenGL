module;
#include "Internal.hpp"

export module Glib.Device.Handle;
import <type_traits>;
import <string_view>;
import Glib.Device.IWindowHandle;
import Glib.Device.Event.API;
export import Glib.Device.IO;

export namespace gl::device
{
	struct [[nodiscard]] log_t { constexpr log_t() noexcept = default; };
	inline constexpr log_t log{};

	class [[nodiscard]] DeviceHandle : public IWindowHandle
	{
	public:
		using base = IWindowHandle;
		using handle_type = base::handle_type;
		using base::base;

		constexpr DeviceHandle& operator=(nullptr_t) noexcept
		{
			base::operator=(nullptr);
			return *this;
		}

		constexpr DeviceHandle& operator=(handle_type&& handle) noexcept
		{
			base::operator=(std::move(handle));
			return *this;
		}

		~DeviceHandle() noexcept
		{
			if (myHandle)
			{
				// TODO: replace with new interface
				//::DestroyWindow(myHandle);
				myHandle = nullptr;
			}
		}

		DeviceHandle(const DeviceHandle&) = delete;
		constexpr DeviceHandle(DeviceHandle&&) noexcept = default;
		DeviceHandle& operator=(const DeviceHandle&) = delete;
		constexpr DeviceHandle& operator=(DeviceHandle&&) noexcept = default;
	};

	[[nodiscard]]
	constexpr NativeRect MakeNativeRect() noexcept
	{
		return {};
	}

	inline bool RegisterWindow(const tagWNDCLASSEXW& property)
	{
		return 0 == ::RegisterClassEx(&property);
	}

	inline bool UnregisterWindow(const HINSTANCE& hinst, const std::wstring_view& class_name)
	{
		return 0 == ::UnregisterClass(class_name.data(), hinst);
	}

	using ::PostQuitMessage;
	using ::DestroyWindow;
	using ::GetLastError;
}
