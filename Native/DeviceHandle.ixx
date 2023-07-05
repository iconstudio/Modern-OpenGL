export module Glib.Device.Handle;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IWindowHandle;

export namespace gl::device
{
	class [[nodiscard]] DeviceHandle : public IWindowHandle
	{
	public:
		using base = IWindowHandle;
		using handle_type = base::handle_type;
		using base::base;

		constexpr DeviceHandle& operator=(handle_type&& handle) noexcept
		{
			base::operator=(std::move(handle));
			return *this;
		}

		constexpr DeviceHandle& operator=(nullptr_t) noexcept
		{
			base::operator=(nullptr);
			return *this;
		}

		~DeviceHandle() noexcept
		{
			Destroy();
		}

		DeviceHandle(const DeviceHandle&) = delete;
		constexpr DeviceHandle(DeviceHandle&&) noexcept = default;
		DeviceHandle& operator=(const DeviceHandle&) = delete;
		constexpr DeviceHandle& operator=(DeviceHandle&&) noexcept = default;
	};
}
