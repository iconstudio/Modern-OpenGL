module;
#include "Internal.hpp"

export module Glib.Device.Event;
import <compare>;
export import :ID;

export namespace gl::device
{
	struct [[nodiscard]] Event final
	{
		constexpr Event() noexcept = default;
		constexpr ~Event() noexcept = default;

		explicit constexpr Event(const RawEvent& msg) noexcept
			: id(EventID{ msg.message })
			, wParam(msg.wParam), lParam(msg.lParam)
			, time(msg.time)
		{}

		explicit constexpr Event(RawEvent&& msg) noexcept
			: id(EventID{ std::move(msg.message) })
			, wParam(std::move(msg.wParam)), lParam(std::move(msg.lParam))
			, time(std::move(msg.time))
		{}

		explicit constexpr Event(const EventID& msg, const unsigned long long& lhs, const long long& rhs, const unsigned long& tick) noexcept
			: id(msg), wParam(lhs), lParam(rhs)
			, time(tick)
		{}

		[[nodiscard]]
		constexpr bool operator==(const Event& rhs) const noexcept = default;

		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const Event& rhs) const noexcept = default;

		constexpr Event(const Event&) noexcept = default;
		constexpr Event(Event&&) noexcept = default;
		constexpr Event& operator=(const Event&) noexcept = default;
		constexpr Event& operator=(Event&&) noexcept = default;

		EventID id = EventID::None;
		unsigned long long wParam = 0;
		long long lParam = 0;
		unsigned long time = 0;
	};

	namespace kb
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

	namespace mb
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

		inline constexpr MouseEventID MovedOutside{ EventID::NCMouseMove };
	};
}
