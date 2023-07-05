export module Glib.Device.Context;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IContext;

export namespace gl::device
{
	class [[nodiscard]] DeviceContext : public IContext
	{
	public:
		using base = IContext;

		explicit constexpr DeviceContext(const handle_type& hdc) noexcept
			: base(hdc)
		{}

		constexpr DeviceContext(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		constexpr DeviceContext(base&& handle) noexcept
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
