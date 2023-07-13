export module Glib.Windows.ProcessInstance;
import <type_traits>;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;

export namespace gl::win32
{
	class [[nodiscard]] ProcessInstance : public IHandle<native::HINSTANCE>
	{
	public:
		using base = IHandle<native::HINSTANCE>;

		constexpr ProcessInstance() noexcept = default;
		constexpr ~ProcessInstance() noexcept = default;

		constexpr ProcessInstance(native::HINSTANCE handle) noexcept
			: base(handle)
		{}

		ProcessInstance(const ProcessInstance&) = delete;
		ProcessInstance(ProcessInstance&&) = default;
		ProcessInstance& operator=(const ProcessInstance&) = delete;
		ProcessInstance& operator=(ProcessInstance&&) = default;
	};

	[[nodiscard]]
	ProcessInstance GetProcessInstance() noexcept;
}
