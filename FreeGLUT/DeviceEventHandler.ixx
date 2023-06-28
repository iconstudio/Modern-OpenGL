module;
#include "Internal.hpp"

export module Glib.Device.Event.Handler;
import Utility;
export import Glib.Device.Event;

export namespace gl::device
{
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

		static bool Push(const HWND& hwnd, const EventID& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, static_cast<DeviceCommandIDType>(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, EventID&& id, const unsigned long long& lhs, const long long& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, static_cast<DeviceCommandIDType>(id), lhs, rhs);
		}

		static bool Push(const HWND& hwnd, EventID&& id, unsigned long long&& lhs, long long&& rhs) noexcept
		{
			return 0 != ::PostMessage(hwnd, static_cast<DeviceCommandIDType>(id), util::move(lhs), util::move(rhs));
		}

		static bool Push(const HWND& hwnd, const Event& msg) noexcept
		{
			return Push(hwnd, msg.id, msg.wParam, msg.lParam);
		}

		static bool Push(const HWND& hwnd, Event&& msg) noexcept
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
