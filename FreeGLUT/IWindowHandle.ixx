module;
#include "Internal.hpp"

export module Glib.Device.IWindowHandle;
import <type_traits>;
import <string_view>;
import Glib.Device.IHandle;
import Glib.Device.Event.API;
export import Glib.Device.IO; 

export namespace gl::device
{
	using RawDeviceHandle = ::HWND__*;
	using HWND = ::HWND__*;
	using NativeRect = tagRECT;

	class [[nodiscard]] IWindowHandle : public IHandle<RawDeviceHandle>
	{
	public:
		using base = IHandle<RawDeviceHandle>;
		using handle_type = base::handle_type;
		using base::base;

	};
}
