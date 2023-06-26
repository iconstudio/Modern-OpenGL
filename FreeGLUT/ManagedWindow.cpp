module;
#include <algorithm>

module Glib.Window.ManagedWindow;
import Utility;

gl::window::ManagedWindow::ManagedWindow(Window&& window) noexcept
	: underlying(std::move(window))
	, optionFullscreen(false)
	, myEventHandlers()
	, std::enable_shared_from_this<ManagedWindow>()
{
	myDimensions = underlying.GetDimensions();
	myEventHandlers.reserve(20);
}
