module;
#include "Internal.hpp"
export module Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ::HINSTANCE__;
	using ::HMODULE;
	using HINSTANCE = HINSTANCE__*;

	class [[nodiscard]] ProcessInstance
	{
	public:
		constexpr ProcessInstance() noexcept = default;
		constexpr ~ProcessInstance() noexcept = default;

		constexpr ProcessInstance(HINSTANCE handle) noexcept
			: myHandle(handle)
		{}

		HINSTANCE__* myHandle = nullptr;

		ProcessInstance(const ProcessInstance&) = delete;
		ProcessInstance(ProcessInstance&&) = default;
		ProcessInstance& operator=(const ProcessInstance&) = delete;
		ProcessInstance& operator=(ProcessInstance&&) = default;
	};

	[[nodiscard]]
	inline ProcessInstance GetProcessInstance() noexcept
	{
		return ProcessInstance{ ::GetModuleHandle(NULL) };
	}
}
