module;
#include "Internal.hpp"

export module Glib.Windows.ProcessInstance;
import <type_traits>;

export namespace gl::win32
{
	using HINSTANCE = HINSTANCE__*;

	class [[nodiscard]] ProcessInstance
	{
	public:
		constexpr ProcessInstance() noexcept = default;
		constexpr ~ProcessInstance() noexcept = default;

		constexpr ProcessInstance(HINSTANCE__* handle) noexcept
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
