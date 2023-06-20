module;
#include "Internal.hpp"
export module Glib.Device.Command;

export namespace gl::device
{
	struct get_result_t { constexpr get_result_t() noexcept = default; };
	inline constexpr get_result_t get_result{};

	using ::MSG, ::tagMSG;
	using Trigger = ::tagMSG;

	enum class [[nodiscard]] PeekCmd : unsigned int
	{
		Remove = PM_REMOVE,
		DontRemove = PM_NOREMOVE,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD
	};

	class CommandQueue
	{
	public:
		[[nodiscard]]
		static inline bool Pop(const HWND& hwnd, Trigger& output) noexcept
		{
			return 0 != ::GetMessage(&output, hwnd, 0, 0);
		}

		static inline bool Push(const HWND& hwnd, const UINT& msg, const WPARAM& lhs = 0, const LPARAM& rhs = 0) noexcept
		{
			return 0 != ::PostMessage(hwnd, msg, lhs, rhs);
		}

		static inline bool Peek(const HWND& hwnd, Trigger& output, const PeekCmd& cmd = PeekCmd::DontRemove) noexcept
		{
			return 0 != ::PeekMessage(&output, hwnd, 0, 0, static_cast<unsigned int>(cmd));
		}

		static inline void Process(const Trigger& msg) noexcept
		{
			Translate(msg);
			Dispatch(msg);
		}

		[[nodiscard]]
		static inline LRESULT Dispatch(get_result_t, const Trigger& msg) noexcept
		{
			return ::DispatchMessage(&msg);
		}

		[[nodiscard]]
		static inline bool Translate(get_result_t, const Trigger& msg) noexcept
		{
			return 0 != ::TranslateMessage(&msg);
		}

		[[noreturn]]
		static inline void Translate(const Trigger& msg) noexcept
		{
			::TranslateMessage(&msg);
		}

		[[noreturn]]
		static inline void Dispatch(const Trigger& msg) noexcept
		{
			::DispatchMessage(&msg);
		}
	};
}
