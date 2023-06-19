module;
#include <WinUser.h>
export module Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ProcessInstance = ::HINSTANCE;

	[[nodiscard]]
	inline ProcessInstance GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(nullptr);
	}

	[[nodiscard]]
	inline bool TryGetProcessInstance(ProcessInstance*& output) noexcept
	{
		return 0 != ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, output);
	}

	[[nodiscard]]
	inline bool TryGetProcessInstance(ProcessInstance& output) noexcept
	{
		return 0 != ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, &output);
	}
}
