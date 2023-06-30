export module Glib.Device.Event:Special;
import <compare>;
export import :ID;
export import :Implement;

export namespace gl::device
{
	struct [[nodiscard]] EventIDWrapper
	{
		constexpr EventIDWrapper() noexcept = default;
		constexpr ~EventIDWrapper() noexcept = default;

		explicit constexpr EventIDWrapper(const EventID& event_id) noexcept
			: id(event_id)
		{}

		explicit constexpr EventIDWrapper(EventID&& event_id) noexcept
			: id(std::move(event_id))
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
			return static_cast<unsigned int>(self.id) <=> static_cast<unsigned int>(event_id);
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

	struct [[nodiscard]] KeyboardEventID : public EventIDWrapper
	{
		KeyboardEventID& operator=(EventID) = delete;

	private:
		KeyboardEventID() noexcept = default;

		using EventIDWrapper::EventIDWrapper;
	};

	struct [[nodiscard]] MouseEventID : public EventIDWrapper
	{
		MouseEventID& operator=(EventID) = delete;

	private:
		MouseEventID() noexcept = default;

		using EventIDWrapper::EventIDWrapper;
	};
}
