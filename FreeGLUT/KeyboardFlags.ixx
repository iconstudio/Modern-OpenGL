module;
#include "Internal.hpp"
export module Glib.Device.IO.Keyboard.Flags;

export namespace gl::device::io
{
	enum class KeyboardFlag : int
	{
		None = 0,
		IsReleased = KF_UP,
		Previous = KF_REPEAT,
		IsAlt = KF_ALTDOWN,
		IsMenu = KF_MENUMODE,
		IsDialog = KF_DLGMODE,
		IsExtended = KF_EXTENDED,
	};
}
