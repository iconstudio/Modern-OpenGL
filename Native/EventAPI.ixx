module;
#include "Internal.hpp"

export module Glib.Device.Event.API;
import <type_traits>;
export import Glib.Device.Event;

export namespace gl::device
{
	enum class [[nodiscard]] EventPeeker : unsigned int
	{
		DontRemove = PM_NOREMOVE,
		Remove = PM_REMOVE,
		NoYieldAndDontRemove = PM_NOREMOVE | PM_NOYIELD,
		NoYieldAndRemove = PM_REMOVE | PM_NOYIELD,
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
		static bool Pop(const HWND& hwnd, RawEvent& output) noexcept
		{
			return 0 != ::GetMessage(&output, hwnd, 0, 0);
		}

		static bool Push(const HWND& hwnd, const unsigned int& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, id, lhs, rhs);
		}

		static bool Push(const HWND& hwnd, unsigned int&& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, std::move(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, unsigned int&& id, unsigned long long&& lhs, long long&& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, std::move(id), std::move(lhs), std::move(rhs));
		}

		static bool Push(const HWND& hwnd, const EventID& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return Push(hwnd, static_cast<unsigned int>(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, EventID&& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return Push(hwnd, static_cast<unsigned int>(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, EventID&& id, unsigned long long&& lhs, long long&& rhs) noexcept
		{
			return Push(hwnd, static_cast<unsigned int>(id), std::move(lhs), std::move(rhs));
		}

		static bool Push(const HWND& hwnd, const Event& msg) noexcept
		{
			return Push(hwnd, msg.id, msg.wParam, msg.lParam);
		}

		static bool Push(const HWND& hwnd, Event&& msg) noexcept
		{
			return Push(hwnd, std::move(msg.id), std::move(msg.wParam), std::move(msg.lParam));
		}

		static bool Peek(const HWND& hwnd, RawEvent& output, const EventPeeker& cmd = EventPeeker::DontRemove) noexcept
		{
			return 0 != ::PeekMessage(std::addressof(output), hwnd, 0, 0, static_cast<unsigned int>(cmd));
		}

		static long long Dispatch(const RawEvent& msg) noexcept
		{
			return ::DispatchMessage(&msg);
		}

		static bool Translate(const RawEvent& msg) noexcept
		{
			return 0 != ::TranslateMessage(&msg);
		}

	private:
		EventAPI() = delete;
		~EventAPI() = delete;
		EventAPI(const EventAPI&) = delete;
		EventAPI(EventAPI&&) = delete;
		EventAPI& operator=(const EventAPI&) = delete;
		EventAPI& operator=(EventAPI&&) = delete;
	};
}
