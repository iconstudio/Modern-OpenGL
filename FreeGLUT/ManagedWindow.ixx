export module Glib.ManagedWindow;
import <memory>;
import <vector>;
import Utility;
import Utility.Constraints;
import Utility.Option;
import Utility.Concurrency.Thread;
import Utility.Atomic;
import Glib.Rect;
import Glib.Window;
import Glib.Device.Coroutine;

export namespace gl::window
{
	class [[nodiscard]] ManagedWindow
		: public ::std::enable_shared_from_this<ManagedWindow>
	{
	public:
		explicit ManagedWindow(Window&& window) noexcept
			: underlying(util::move(window))
			, optionFullscreen(false)
			, myEventHandlers()
		{
			myDimensions = underlying.GetDimensions();
			myEventHandlers.reserve(20);
		}

		template<util::invocable<Window&> Fn>
		constexpr void AddEventHandler(Fn&& procedure) noexcept
		{
			myEventHandlers.push_back(util::forward<Fn>(procedure));
		}

		ManagedWindow(const ManagedWindow&) = delete;
		ManagedWindow(ManagedWindow&&) noexcept = default;
		ManagedWindow& operator=(const ManagedWindow&) = delete;
		ManagedWindow& operator=(ManagedWindow&&) noexcept = default;

	private:
		Window underlying;
		Rect myDimensions;

		util::Option<bool> optionFullscreen;

		void* windowProcedureHandle = nullptr;
		std::vector<void*> myEventHandlers;
	};
}
