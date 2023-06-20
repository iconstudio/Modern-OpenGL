module;
#include <Windows.h>
export module Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ::HINSTANCE, ::HINSTANCE__;
	using ::HMODULE;
	using ProcessInstance = HINSTANCE__*;

	[[nodiscard]]
	inline ProcessInstance GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(NULL);
	}
}
