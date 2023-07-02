module;
#include "Internal.hpp"

export module Glib.Device.Event:Implement;
import <type_traits>;

export namespace gl::device
{
	namespace detail
	{
		[[nodiscard]]
		bool Pop(const HWND& hwnd, MSG& output) noexcept
		{
			return 0 != ::GetMessage(&output, hwnd, 0, 0);
		}

		bool Push(const HWND& hwnd, const unsigned int& event_id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, event_id, lhs, rhs);
		}

		bool Push(const HWND& hwnd, unsigned int&& event_id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, std::move(event_id), lhs, rhs);
		}

		bool Push(const HWND& hwnd, const MSG& event) noexcept
		{
			return Push(hwnd, event.message, event.wParam, event.lParam);
		}

		bool Push(const HWND& hwnd, MSG&& event) noexcept
		{
			return Push(hwnd, std::move(event.message), std::move(event.wParam), std::move(event.lParam));
		}
	}
}
