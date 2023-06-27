module;
#include "Internal.hpp"

export module Glib.Device.Command;
import Utility;
import Utility.Monad;

export namespace gl::device
{
	using RawDeviceCommand = ::tagMSG;
	using DeviceCommandIDType = decltype(RawDeviceCommand::message);

	enum class [[nodiscard]] PeekCmd : unsigned int
	{
		DontRemove = PM_NOREMOVE,
		Remove = PM_REMOVE,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
	};

	enum class DeviceCommandID : DeviceCommandIDType
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
		CleanupMemory = WM_NCDESTROY,
		QueryEndSession = WM_QUERYENDSESSION,
	};

	struct [[nodiscard]] DeviceCommand final
	{
		constexpr DeviceCommand() noexcept = default;
		constexpr ~DeviceCommand() noexcept = default;

		constexpr DeviceCommand(const RawDeviceCommand& msg) noexcept
			: id(DeviceCommandID{ msg.message })
			, wParam(msg.wParam), lParam(msg.lParam)
			, time(msg.time)
		{}

		constexpr DeviceCommand(RawDeviceCommand&& msg) noexcept
			: id(DeviceCommandID{ util::move(msg.message) })
			, wParam(util::move(msg.wParam)), lParam(util::move(msg.lParam))
			, time(util::move(msg.time))
		{}

		constexpr DeviceCommand(const DeviceCommandID& msg, const unsigned long long& lhs, const long long& rhs, const unsigned long& tick) noexcept
			: id(msg), wParam(lhs), lParam(rhs)
			, time(tick)
		{}

		constexpr DeviceCommand(const DeviceCommand&) noexcept = default;
		constexpr DeviceCommand(DeviceCommand&&) noexcept = default;
		constexpr DeviceCommand& operator=(const DeviceCommand&) noexcept = default;
		constexpr DeviceCommand& operator=(DeviceCommand&&) noexcept = default;

		DeviceCommandID id;
		unsigned long long wParam;
		long long lParam;
		unsigned long time;
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
		static MsgResult Pop(const HWND& hwnd, RawDeviceCommand& output) noexcept
		{
			return MsgResult{ ::GetMessage(&output, hwnd, 0, 0) };
		}

		static bool Push(const HWND& hwnd, const DeviceCommandIDType& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, id, lhs, rhs);
		}

		static bool Push(const HWND& hwnd, DeviceCommandIDType&& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, util::move(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, DeviceCommandIDType&& id, unsigned long long&& lhs, long long&& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, util::move(id), util::move(lhs), util::move(rhs));
		}

		static bool Push(const HWND& hwnd, const DeviceCommandID& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, static_cast<DeviceCommandIDType>(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, DeviceCommandID&& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, static_cast<DeviceCommandIDType>(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, DeviceCommandID&& id, unsigned long long&& lhs, long long&& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, static_cast<DeviceCommandIDType>(id), util::move(lhs), util::move(rhs));
		}

		static bool Push(const HWND& hwnd, const DeviceCommand& msg) noexcept
		{
			return Push(hwnd, msg.id, msg.wParam, msg.lParam);
		}

		static bool Push(const HWND& hwnd, DeviceCommand&& msg) noexcept
		{
			return Push(hwnd, util::move(msg.id), util::move(msg.wParam), util::move(msg.lParam));
		}

		static MsgResult Peek(const HWND& hwnd, RawDeviceCommand& output, const PeekCmd& cmd = PeekCmd::DontRemove) noexcept
		{
			return MsgResult{ ::PeekMessage(util::addressof(output), hwnd, 0, 0, static_cast<unsigned int>(cmd)) };
		}

		static long long Dispatch(const RawDeviceCommand& msg) noexcept
		{
			return ::DispatchMessage(&msg);
		}

		static bool Translate(const RawDeviceCommand& msg) noexcept
		{
			return 0 != ::TranslateMessage(&msg);
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
