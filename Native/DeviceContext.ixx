export module Glib.Device.Context;
import <type_traits>;
import Glib.Definitions;
export import Glib.Device.IContext;

export namespace gl::device
{
	class [[nodiscard]] DeviceContext : public IContext
	{
	public:
		using base = IContext;

		DeviceContext(const native::HWND& window) noexcept;
		~DeviceContext() noexcept;

		DeviceContext(const DeviceContext&) = delete;
		constexpr DeviceContext(DeviceContext&&) noexcept = default;
		DeviceContext& operator=(const DeviceContext&) = delete;
		constexpr DeviceContext& operator=(DeviceContext&&) noexcept = default;

	private:
		using base::Destroy;

		native::HWND myWindowHandle;
	};

	class [[nodiscard]] GlobalDeviceContext : public IContext
	{
	public:
		using base = IContext;

		GlobalDeviceContext() noexcept;
		~GlobalDeviceContext() noexcept;

		GlobalDeviceContext(const GlobalDeviceContext&) = delete;
		GlobalDeviceContext(GlobalDeviceContext&&) = delete;
		GlobalDeviceContext& operator=(const GlobalDeviceContext&) = delete;
		GlobalDeviceContext& operator=(GlobalDeviceContext&&) = delete;

	private:
		using base::Destroy;
		using base::Release;
		using base::operator=;
	};
}
