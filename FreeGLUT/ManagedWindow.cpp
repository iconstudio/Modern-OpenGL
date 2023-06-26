module;
#include <algorithm>
module Glib.Window.ManagedWindow;

using namespace gl;
using namespace gl::window;

ManagedWindow::ManagedWindow(Window&& window) noexcept
	: underlying(util::move(window))
	, optionFullscreen(false)
	, myEventHandlers()
	, std::enable_shared_from_this<ManagedWindow>()
{
	myDimensions = underlying.GetDimensions();
	myEventHandlers.reserve(20);
}

void ManagedWindow::AddEventHandler(event_id_t id, void* const& procedure) noexcept
{
	myEventHandlers.push_back(std::make_pair(id, procedure));

	std::sort(myEventHandlers.begin(), myEventHandlers.end()
		, [](const event_t& a, const event_t& b) noexcept {
		return a.first < b.first;
	});
}

void EventHandler() noexcept
{

}
