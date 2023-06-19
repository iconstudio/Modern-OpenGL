module;
#include <Windows.h>
export module Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ::HINSTANCE;

	[[nodiscard]]
	inline HINSTANCE GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(nullptr);
	}

	[[nodiscard]]
	inline bool TryGetProcessInstance(HINSTANCE* const& output) noexcept
	{
		return 0 != ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, output);
	}

	[[nodiscard]]
	inline bool TryGetProcessInstance(HINSTANCE& output) noexcept
	{
		return 0 != ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, &output);
	}
}
