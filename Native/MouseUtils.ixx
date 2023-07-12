module;
#include "Internal.hpp"
export module Glib.Device.IO.Mouse:Utils;

export namespace gl::win32::io
{
	/// <summary>
	/// Only on the main thread
	/// </summary>
	void CaptureMouse(const HWND& handle) noexcept
	{
		::SetCapture(handle);
	}

	/// <summary>
	/// Only on the main thread
	/// </summary>
	[[nodiscard]]
	bool IsMouseCaptured(const HWND& handle) noexcept
	{
		return ::GetCapture() == handle;
	}

	/// <summary>
	/// Only on the main thread
	/// </summary>
	void ResetMouseCapture(const HWND& handle) noexcept
	{
		if (IsMouseCaptured(handle))
		{
			::ReleaseCapture();
		}
	}

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
