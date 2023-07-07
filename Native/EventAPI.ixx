export module Glib.Device.Event.API;
import <type_traits>;
export import Glib.Definitions;
export import Glib.Device.Event;

export namespace gl::device
{
	enum class [[nodiscard]] EventPeeker : unsigned int
	{
		DontRemove = 0U, // PM_NOREMOVE,
		Remove = 1U, // PM_REMOVE,
		NoYieldAndDontRemove = 2U, // PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = 3U, // PM_REMOVE | PM_NOYIELD,
	};

	class EventAPI final
	{
	public:
		[[nodiscard]]
		static consteval RawEvent MakeEvent() noexcept
		{
			return {};
		}

		[[nodiscard]]
		static bool Pop(const native::HWND& hwnd, RawEvent& output) noexcept;
		static bool Push(const native::HWND& hwnd, const unsigned int& id, const unsigned long long& lhs, const long long& rhs) noexcept;
		static bool Push(const native::HWND& hwnd, unsigned int&& id, const unsigned long long& lhs, const long long& rhs) noexcept;
		static bool Push(const native::HWND& hwnd, unsigned int&& id, unsigned long long&& lhs, long long&& rhs) noexcept;
		static bool Push(const native::HWND& hwnd, const EventID& id, const unsigned long long& lhs, const long long& rhs) noexcept;
		static bool Push(const native::HWND& hwnd, EventID&& id, const unsigned long long& lhs, const long long& rhs) noexcept;
		static bool Push(const native::HWND& hwnd, EventID&& id, unsigned long long&& lhs, long long&& rhs) noexcept;
		static bool Push(const native::HWND& hwnd, const Event& msg) noexcept;
		static bool Push(const native::HWND& hwnd, Event&& msg) noexcept;

		static bool Peek(const native::HWND& hwnd, RawEvent& output, const EventPeeker& cmd = EventPeeker::DontRemove) noexcept;

		static long long Dispatch(const RawEvent& msg) noexcept;
		static bool Translate(const RawEvent& msg) noexcept;

	private:
		EventAPI() = delete;
		~EventAPI() = delete;
		EventAPI(const EventAPI&) = delete;
		EventAPI(EventAPI&&) = delete;
		EventAPI& operator=(const EventAPI&) = delete;
		EventAPI& operator=(EventAPI&&) = delete;
	};
}
