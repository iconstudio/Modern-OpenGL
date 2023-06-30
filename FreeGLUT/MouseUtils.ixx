module;
#include "Internal.hpp"
export module Glib.Device.IO.Mouse:Utils;

export namespace gl::device::io
{
	inline bool EnablePointingDevice() noexcept
	{
		return FALSE != ::EnableMouseInPointer(TRUE);
	}

	inline bool DisablePointingDevice() noexcept
	{
		return FALSE != ::EnableMouseInPointer(FALSE);
	}

	/// <summary>
	/// Is support pen or touch input?
	/// </summary>
	[[nodiscard]]
	inline bool IsPointingDeviceEnabled() noexcept
	{
		return FALSE != ::IsMouseInPointerEnabled();
	}
}
