module;
module Glib.Window.ManagedWindow;
import <exception>;

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

gl::window::managed_window::AwakeResult
gl::window::ManagedWindow::Awake()
noexcept
{
	try
	{
		for (size_t index = 0; index < workerCount; ++index)
		{
			myWorkers.emplace_back(std::make_unique<util::jthread>(Worker, cancellationSource.get_token(), std::ref(*this), std::ref(awaitFlag)));
		}
	}
	catch (...)
	{
		return managed_window::AwakeResult::FailedOnCreatingWorkers;
	}

	try
	{
		myCoroutines = std::make_unique<coro_storage>();
	}
	catch (...)
	{
		return managed_window::AwakeResult::FailedOnCreatingCoroutines;
	}

	underlying.Awake();
	underlying.Start();
}
