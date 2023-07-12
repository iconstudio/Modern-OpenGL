export module Glib.Windows.Handle;
import <type_traits>;
import Glib.Windows.Definitions;
import Glib.Windows.IWindow;

export namespace gl::win32
{
	class [[nodiscard]] DeviceHandle : public IWindow
	{
	public:
		using base = IWindow;
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
