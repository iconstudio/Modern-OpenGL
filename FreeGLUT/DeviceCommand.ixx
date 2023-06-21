module;
#include "Internal.hpp"
export module Glib.Device.Command;
import Utility.Monad;

export namespace gl::device
{
	struct get_result_t { constexpr get_result_t() noexcept = default; };
	inline constexpr get_result_t get_result{};

	using DeviceCommand = ::tagMSG;

	enum class [[nodiscard]] PeekCmd : unsigned int
	{
		DontRemove = PM_NOREMOVE,
		Remove = PM_REMOVE,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
	};

	enum class [[nodiscard]] MsgResult : int
	{
		Quit = 0,
		Unknown = -1
	};

	class CommandQueue
	{
	public:
		[[nodiscard]]
		static inline MsgResult Pop(const HWND& hwnd, DeviceCommand& output) noexcept
		{
			return MsgResult{ ::GetMessage(&output, hwnd, 0, 0) };
		}

		static inline bool Push(const HWND& hwnd, const UINT& msg, const WPARAM& lhs = 0, const LPARAM& rhs = 0) noexcept
		{
			return 0 != ::PostMessage(hwnd, msg, lhs, rhs);
		}

		static inline MsgResult Peek(const HWND& hwnd, DeviceCommand& output, const PeekCmd& cmd = PeekCmd::DontRemove) noexcept
		{
			return MsgResult{ ::PeekMessage(&output, hwnd, 0, 0, static_cast<unsigned int>(cmd)) };
		}

		[[nodiscard]]
		static inline util::Monad<LRESULT> Process(get_result_t, const DeviceCommand& msg) noexcept
		{
			if (Translate(get_result, msg))
			{
				return Dispatch(get_result, msg);
			}
			else
			{
				return util::nullopt;
			}
		}

		static inline void Process(const DeviceCommand& msg) noexcept
		{
			Translate(msg);
			Dispatch(msg);
		}

		[[nodiscard]]
		static inline LRESULT Dispatch(get_result_t, const DeviceCommand& msg) noexcept
		{
			return ::DispatchMessage(&msg);
		}

		[[nodiscard]]
		static inline bool Translate(get_result_t, const DeviceCommand& msg) noexcept
		{
			return 0 != ::TranslateMessage(&msg);
		}

		[[noreturn]]
		static inline void Dispatch(const DeviceCommand& msg) noexcept
		{
			::DispatchMessage(&msg);
		}

		[[noreturn]]
		static inline void Translate(const DeviceCommand& msg) noexcept
		{
			::TranslateMessage(&msg);
		}
	};
}
