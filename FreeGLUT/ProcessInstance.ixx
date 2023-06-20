module;
#include <Windows.h>
export module Glib.Device.ProcessInstance;

export namespace gl::device
{
	using ::HINSTANCE;
	using ::HMODULE;

	[[nodiscard]]
	inline HINSTANCE__* GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(NULL);
	}
}
