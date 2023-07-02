module;
module Glib.Window.ManagedWindow;

explicit
gl::window::ManagedWindow::ManagedWindow(gl::window::Window&& window, int number_of_workers)
	: underlying(std::move(window))
	, workerCount(number_of_workers), terminateLatch(number_of_workers)
	, base_shared_t()
{
	myDimensions = underlying.GetDimensions();
	myEventHandlers.reserve(20);
	myWorkers.reserve(number_of_workers);

	underlying.SetInternalUserData(reinterpret_cast<long long>(this));
}

