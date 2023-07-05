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
}
