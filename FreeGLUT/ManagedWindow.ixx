export module Glib.Window.ManagedWindow;
import <utility>;
import <memory>;
import <vector>;
import Utility;
import Utility.Constraints;
import Utility.Option;
import Utility.Concurrency.Thread;
import Utility.Concurrency.Thread.Unit;
import Utility.Atomic;
import Utility.String;
import Utility.FixedString;
import Glib.Rect;
import Glib.Window;
import Glib.Device.Coroutine;

void EventHandler() noexcept;

export namespace gl::window
{
	class [[nodiscard]] ManagedWindow
		: public ::std::enable_shared_from_this<ManagedWindow>
	{
	public:
		using unit_t = std::unique_ptr<util::ThreadUnit>;
		using pool_t = std::vector<unit_t>;
		using event_id_t = typename device::DeviceCommandIDType;
		using event_handler_t = void*;
		using event_t = std::pair<event_id_t, event_handler_t>;

		explicit ManagedWindow(Window&& window) noexcept;

		void AddEventHandler(event_id_t id, void* const& procedure) noexcept;

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) noexcept = default;
		ManagedWindow& operator=(const ManagedWindow&) = delete;
		ManagedWindow& operator=(ManagedWindow&&) noexcept = default;

	private:
		friend void EventHandler() noexcept;

		Window underlying;
		Rect myDimensions;

		util::Option<bool> optionFullscreen;

		void* windowProcedureHandle = nullptr;
		bool isRenderingNow = false;

		// flat map
		std::vector<event_t> myEventHandlers;
		pool_t myWorkers;
		util::atomic<device::DeviceCommand> awaitFlags;
	};
}
