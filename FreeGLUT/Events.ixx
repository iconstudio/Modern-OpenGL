module;
#include "Internal.hpp"

export module Glib.Device.Event:Definitions;
import <compare>;

namespace gl::device
{
	export using RawDeviceCommand = ::tagMSG;
	export using DeviceCommandIDType = decltype(RawDeviceCommand::message);

	export enum class [[nodiscard]] EventID : DeviceCommandIDType
	{
		None = 0,
		Create = WM_CREATE,
		Destroy = WM_DESTROY,

		Move = WM_MOVE,
		Size = WM_SIZE,
		Activate = WM_ACTIVATE,
		SetKeyboardFocus = WM_SETFOCUS,
		KillKeyboardFocus = WM_KILLFOCUS,
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
		SysCommand = WM_SYSCOMMAND,

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

	struct [[nodiscard]] EventIDWrapper
	{
		constexpr EventIDWrapper() noexcept = default;
		constexpr ~EventIDWrapper() noexcept = default;

		explicit constexpr EventIDWrapper(const EventID& event_id) noexcept
			: id(event_id)
		{}

		explicit constexpr EventIDWrapper(EventID&& event_id) noexcept
			: id(static_cast<EventID&&>(event_id))
		{}

		[[nodiscard]]
		inline friend constexpr
			bool
			operator==(const EventIDWrapper& self, const EventID& event_id) noexcept
		{
			return self.id == event_id;
		}

		[[nodiscard]]
		inline friend constexpr
			std::strong_ordering
			operator<=>(const EventIDWrapper& self, const EventID& event_id) noexcept
		{
			return static_cast<DeviceCommandIDType>(self.id) <=> static_cast<DeviceCommandIDType>(event_id);
		}

		constexpr operator EventID& () & noexcept
		{
			return id;
		}

		constexpr operator const EventID& () const& noexcept
		{
			return id;
		}

		constexpr operator EventID && () && noexcept
		{
			return static_cast<EventID&&>(id);
		}

		constexpr operator const EventID && () const&& noexcept
		{
			return static_cast<const EventID&&>(id);
		}

		constexpr EventIDWrapper(const EventIDWrapper&) noexcept = default;
		constexpr EventIDWrapper(EventIDWrapper&&) noexcept = default;
		constexpr EventIDWrapper& operator=(const EventIDWrapper&) noexcept = default;
		constexpr EventIDWrapper& operator=(EventIDWrapper&&) noexcept = default;
		constexpr bool operator==(const EventIDWrapper&) const noexcept = default;
		constexpr std::strong_ordering operator<=>(const EventIDWrapper&) const noexcept = default;

		EventIDWrapper& operator=(EventID) = delete;

		EventID id = EventID::None;
	};

	export struct [[nodiscard]] KeyboardEventID : public EventIDWrapper
	{
		static inline constexpr EventID GUARD_FIRST = EventID{ WM_KEYFIRST };
		static inline constexpr EventID GUARD_LAST = EventID{ WM_KEYLAST };

		KeyboardEventID& operator=(EventID) = delete;

	private:
		using EventIDWrapper::EventIDWrapper;
	};

	export namespace kb
	{
		inline constexpr KeyboardEventID Pressed{ EventID::KeyDown };
		inline constexpr KeyboardEventID Released{ EventID::KeyUp };
		inline constexpr KeyboardEventID CharPressed{ EventID::Char };
		inline constexpr KeyboardEventID CharReleased{ EventID::DeadChar };

		inline constexpr KeyboardEventID AltPressed{ EventID::SysKeyDown };
		inline constexpr KeyboardEventID AltReleased{ EventID::SysKeyUp };
		inline constexpr KeyboardEventID AltCharPressed{ EventID::SysChar };
		inline constexpr KeyboardEventID AltCharReleased{ EventID::SysDeadChar };
	}

	export struct [[nodiscard]] MouseEventID : public EventIDWrapper
	{
		static inline constexpr EventID GUARD_FIRST = EventID{ WM_MOUSEFIRST };
		static inline constexpr EventID GUARD_LAST = EventID{ WM_MOUSELAST };

		MouseEventID& operator=(EventID) = delete;

	private:
		using EventIDWrapper::EventIDWrapper;
	};

	export namespace mb
	{
		inline constexpr MouseEventID Moved{ EventID::MouseMove };
		inline constexpr MouseEventID Covered{ EventID::MouseHover };
		inline constexpr MouseEventID Uncovered{ EventID::MouseLeave };

		inline constexpr MouseEventID VtWheel{ EventID::MouseWheel };
		inline constexpr MouseEventID HvWheel{ EventID::MouseHWheel };

		inline constexpr MouseEventID LtPressed{ EventID::LButtonDown };
		inline constexpr MouseEventID LtReleased{ EventID::LButtonUp };
		inline constexpr MouseEventID LtDoubleClicked{ EventID::LButtonDoubleClick };

		inline constexpr MouseEventID RtPressed{ EventID::RButtonDown };
		inline constexpr MouseEventID RtReleased{ EventID::RButtonUp };
		inline constexpr MouseEventID RtDoubleClicked{ EventID::RButtonDoubleClick };

		inline constexpr MouseEventID MdPressed{ EventID::MButtonDown };
		inline constexpr MouseEventID MdReleased{ EventID::MButtonUp };
		inline constexpr MouseEventID MdDoubleClicked{ EventID::MButtonDoubleClick };
	};
}
