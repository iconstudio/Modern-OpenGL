module;
#include <Windows.h>
export module Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ::HINSTANCE__;
	using HINSTANCE = ::HINSTANCE;
	using ::HMODULE;
	using ProcessInstance = struct HINSTANCE__*;

	[[nodiscard]]
	inline ProcessInstance GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(NULL);
	}
}
