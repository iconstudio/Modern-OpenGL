module;
#include <Windows.h>
export module Glib.Device.ProcessInstance;

export using ::HINSTANCE;
export using ::HMODULE;

export namespace gl::device
{
	using ::HINSTANCE;
	using ::HMODULE;

	[[nodiscard]]
	inline HINSTANCE GetProcessInstance() noexcept
	{
		return ::GetModuleHandle(nullptr);
	}
}
