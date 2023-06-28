module;
#include "Internal.hpp"

export module Glib.Device.Event;
import <compare>;
import Utility;
export import :Definitions;

export namespace gl::device
{
	enum class [[nodiscard]] PeekCmd : unsigned int
	{
		DontRemove = PM_NOREMOVE,
		Remove = PM_REMOVE,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
	};

	/// <summary>
	/// WPARAM from EventID::Activate
	/// </summary>
	enum class [[nodiscard]] DeviceActivation : unsigned short
	{
		Activated = WA_ACTIVE,
		ClickActive = WA_CLICKACTIVE,
		Inactivated = WA_INACTIVE,
	};

	[[nodiscard]]
	constexpr bool operator==(const DeviceActivation& state, const unsigned short& rhs) noexcept
	{
		return static_cast<unsigned short>(state) == rhs;
	}

#ifdef Event
#undef Event
#endif
	struct [[nodiscard]] Event final
	{
		constexpr Event() noexcept = default;
		constexpr ~Event() noexcept = default;

		constexpr Event(const RawDeviceCommand& msg) noexcept
			: id(EventID{ msg.message })
			, wParam(msg.wParam), lParam(msg.lParam)
			, time(msg.time)
		{}

		constexpr Event(RawDeviceCommand&& msg) noexcept
			: id(EventID{ util::move(msg.message) })
			, wParam(util::move(msg.wParam)), lParam(util::move(msg.lParam))
			, time(util::move(msg.time))
		{}

		constexpr Event(const EventID& msg, const unsigned long long& lhs, const long long& rhs, const unsigned long& tick) noexcept
			: id(msg), wParam(lhs), lParam(rhs)
			, time(tick)
		{}

		[[nodiscard]]
		constexpr bool operator==(const Event& rhs) const noexcept
		{
			return id == rhs.id && wParam == rhs.wParam && lParam == rhs.lParam;
		}

		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const Event& rhs) const noexcept
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

		constexpr Event(const Event&) noexcept = default;
		constexpr Event(Event&&) noexcept = default;
		constexpr Event& operator=(const Event&) noexcept = default;
		constexpr Event& operator=(Event&&) noexcept = default;

		EventID id = EventID::None;
		unsigned long long wParam = 0;
		long long lParam = 0;
		unsigned long time = 0;
	};
}
