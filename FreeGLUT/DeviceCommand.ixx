module;
#include "Internal.hpp"

export module Glib.Device.Command;
import <compare>;
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
		Quit = WM_QUIT,
		CleanupMemory = WM_NCDESTROY,

		KeyDown = WM_KEYDOWN,
		KeyUp = WM_KEYUP,
		Char = WM_CHAR,
		DeadChar = WM_DEADCHAR,

		SysKeyDown = WM_SYSKEYDOWN,
		SysKeyUp = WM_SYSKEYUP,
		SysChar = WM_SYSCHAR,
		SysDeadChar = WM_SYSDEADCHAR,

		MouseMove = WM_MOUSEMOVE,
		MouseHover = WM_MOUSEHOVER,
		MouseLeave = WM_MOUSELEAVE,
		MouseWheel = WM_MOUSEWHEEL,
		MouseHWheel = WM_MOUSEHWHEEL,
		LButtonDown = WM_LBUTTONDOWN,
		LButtonUp = WM_LBUTTONUP,
		LButtonDoubleClick = WM_LBUTTONDBLCLK,
		RButtonDown = WM_RBUTTONDOWN,
		RButtonUp = WM_RBUTTONUP,
		RButtonDoubleClick = WM_RBUTTONDBLCLK,
		MButtonDown = WM_MBUTTONDOWN,
		MButtonUp = WM_MBUTTONUP,
		MButtonDoubleClick = WM_MBUTTONDBLCLK,

		ChangedCapture = WM_CAPTURECHANGED,
	};

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

		[[nodiscard]]
		constexpr bool operator==(const DeviceCommand& rhs) const noexcept
		{
			return id == rhs.id && wParam == rhs.wParam && lParam == rhs.lParam;
		}

		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const DeviceCommand& rhs) const noexcept
		{
			auto comp_id = id <=> rhs.id;
			if (comp_id != std::strong_ordering::equal)
			{
				return comp_id;
			}

			auto comp_wp = wParam <=> rhs.wParam;
			if (comp_wp != std::strong_ordering::equal)
			{
				return comp_wp;
			}

			auto comp_lp = lParam <=> rhs.wParam;
			if (comp_lp != std::strong_ordering::equal)
			{
				return comp_lp;
			}

			return time <=> rhs.time;
		}

		constexpr DeviceCommand(const DeviceCommand&) noexcept = default;
		constexpr DeviceCommand(DeviceCommand&&) noexcept = default;
		constexpr DeviceCommand& operator=(const DeviceCommand&) noexcept = default;
		constexpr DeviceCommand& operator=(DeviceCommand&&) noexcept = default;

		DeviceCommandID id = DeviceCommandID::None;
		unsigned long long wParam = 0;
		long long lParam = 0;
		unsigned long time = 0;
	};

	class DeviceCommandAPI final
	{
	public:
		[[nodiscard]]
		static bool Pop(const HWND& hwnd, RawDeviceCommand& output) noexcept
		{
			return 0 != ::GetMessage(&output, hwnd, 0, 0);
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

		static bool Peek(const HWND& hwnd, RawDeviceCommand& output, const PeekCmd& cmd = PeekCmd::DontRemove) noexcept
		{
			return 0 != ::PeekMessage(util::addressof(output), hwnd, 0, 0, static_cast<unsigned int>(cmd));
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
