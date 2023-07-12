module;
#include "Internal.hpp"
#include <type_traits>
export module Glib.Device.ProcessInstance;

export namespace gl::win32
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

		constexpr ProcessInstance& operator=(nullptr_t) noexcept
		{
			myHandle = nullptr;
			return *this;
		}

		ProcessInstance(const ProcessInstance&) = delete;
		ProcessInstance(ProcessInstance&&) = default;
		ProcessInstance& operator=(const ProcessInstance&) = delete;
		ProcessInstance& operator=(ProcessInstance&&) = default;

		HINSTANCE__* myHandle = nullptr;
	};

	[[nodiscard]]
	inline ProcessInstance GetProcessInstance() noexcept
	{
		return ProcessInstance{ ::GetModuleHandle(NULL) };
	}

	using ::GetLastError;
}
