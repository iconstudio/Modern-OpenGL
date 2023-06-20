module;
#include "Internal.hpp"

export module Glib.Device.Message;

export namespace gl::device
{
	using ::MSG, ::tagMSG;
	using RawDeviceMessage = ::tagMSG;

	[[nodiscard]]
	BOOL __GetMessage(const HWND& hwnd, RawDeviceMessage& msg) noexcept
	{
		return GetMessage(&msg, hwnd, 0, 0);
	}

	BOOL __TranslateMessage(const RawDeviceMessage& msg) noexcept
	{
		return TranslateMessage(&msg);
	}

	LRESULT __DispatchMessage(const RawDeviceMessage& msg) noexcept
	{
		return DispatchMessage(&msg);
	}

	inline void test_msg() noexcept
	{
		MSG Message;
		while (GetMessage(&Message, 0, 0, 0))
		{
			TranslateMessage(&Message);

			DispatchMessage(&Message);
		}
	}

	class DeviceMessage
	{
	public:
		::MSG myMsg;
	};
}
