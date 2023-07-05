export module Glib.Device.Context;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IContext;

export namespace gl::device
{
	class [[nodiscard]] DeviceContext : public IContext
	{
	public:
		using base = IContext;

		DeviceContext(const native::HWND& window) noexcept;

		explicit constexpr DeviceContext(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		~DeviceContext() noexcept;

		DeviceContext(const DeviceContext&) = delete;
		constexpr DeviceContext(DeviceContext&&) noexcept = default;
		DeviceContext& operator=(const DeviceContext&) = delete;
		constexpr DeviceContext& operator=(DeviceContext&&) noexcept = default;

	private:
		native::HWND myWindowHandle;
	};

	class [[nodiscard]] GlobalDeviceContext
	{
	public:
		GlobalDeviceContext() noexcept;
		~GlobalDeviceContext() noexcept;

		constexpr operator DeviceContext& () & noexcept
		{
			return myContext;
		}

		constexpr operator const DeviceContext& () const& noexcept
		{
			return myContext;
		}

		constexpr operator DeviceContext && () && noexcept
		{
			return std::move(myContext);
		}

		constexpr operator const DeviceContext && () const&& noexcept
		{
			return std::move(myContext);
		}

		GlobalDeviceContext(const GlobalDeviceContext&) = delete;
		GlobalDeviceContext(GlobalDeviceContext&&) = delete;
		GlobalDeviceContext& operator=(const GlobalDeviceContext&) = delete;
		GlobalDeviceContext& operator=(GlobalDeviceContext&&) = delete;

	private:
		DeviceContext myContext;
	};
}
