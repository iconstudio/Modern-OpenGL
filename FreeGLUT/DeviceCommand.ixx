module;
#include "Internal.hpp"

export module Glib.Device.Command;
import Utility.Monad;

export namespace gl::device
{
	struct get_result_t { constexpr get_result_t() noexcept = default; };
	inline constexpr get_result_t get_result{};

	using ::HWND__;
	using ::HWND;
	using ::tagMSG;
	using ::MSG;
	using UINT = ::UINT;

	using RawDeviceCommand = ::tagMSG;
	using DeviceCommandIDType = unsigned int; //decltype(RawDeviceCommand::message);

	enum class [[nodiscard]] PeekCmd : unsigned int
	{
		DontRemove = PM_NOREMOVE,
		Remove = PM_REMOVE,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
	};

	enum class DeviceCommand : DeviceCommandIDType
	{
		None = 0,
		Quit = WM_QUIT,
		Create = WM_CREATE,
		Destroy = WM_DESTROY,
		Move = WM_MOVE,
		Size = WM_SIZE,
		Activate = WM_ACTIVATE,
		SetFocus = WM_SETFOCUS,
		KillFocus = WM_KILLFOCUS,
		Enable = WM_ENABLE,
		SetRedraw = WM_SETREDRAW,
		SetText = WM_SETTEXT,
		GetText = WM_GETTEXT,
		GetTextLength = WM_GETTEXTLENGTH,
		Paint = WM_PAINT,
		Close = WM_CLOSE,
		QueryEndSession = WM_QUERYENDSESSION,
	};

	enum class [[nodiscard]] MsgResult : int
	{
		Quit = 0,
		Unknown = -1
	};

	class DeviceCommandAPI final
	{
	public:
		[[nodiscard]]
		static inline MsgResult Pop(const HWND& hwnd, RawDeviceCommand& output) noexcept
		{
			return MsgResult{ ::GetMessage(&output, hwnd, 0, 0) };
		}

		static inline bool Push(const HWND& hwnd, const UINT& msg, const WPARAM& lhs = 0, const LPARAM& rhs = 0) noexcept
		{
			return 0 != ::PostMessage(hwnd, msg, lhs, rhs);
		}

		static inline MsgResult Peek(const HWND& hwnd, RawDeviceCommand& output, const PeekCmd& cmd = PeekCmd::DontRemove) noexcept
		{
			return MsgResult{ ::PeekMessage(&output, hwnd, 0, 0, static_cast<unsigned int>(cmd)) };
		}

		[[nodiscard]]
		static inline util::Monad<LRESULT> Process(get_result_t, const RawDeviceCommand& msg) noexcept
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

		static inline void Process(const RawDeviceCommand& msg) noexcept
		{
			Translate(msg);
			Dispatch(msg);
		}

		[[nodiscard]]
		static inline LRESULT Dispatch(get_result_t, const RawDeviceCommand& msg) noexcept
		{
			return ::DispatchMessage(&msg);
		}

		[[nodiscard]]
		static inline bool Translate(get_result_t, const RawDeviceCommand& msg) noexcept
		{
			return 0 != ::TranslateMessage(&msg);
		}

		[[noreturn]]
		static inline void Dispatch(const RawDeviceCommand& msg) noexcept
		{
			::DispatchMessage(&msg);
		}

		[[noreturn]]
		static inline void Translate(const RawDeviceCommand& msg) noexcept
		{
			::TranslateMessage(&msg);
		}

	private:
		DeviceCommandAPI() = delete;
		~DeviceCommandAPI() = delete;
		DeviceCommandAPI(const DeviceCommandAPI&) = delete;
		DeviceCommandAPI(DeviceCommandAPI&&) = delete;
		DeviceCommandAPI& operator=(const DeviceCommandAPI&) = delete;
		DeviceCommandAPI& operator=(DeviceCommandAPI&&) = delete;
	};
}
