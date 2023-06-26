export module Glib.ManagedWindow;
import <memory>;
import Glib.Window;
import Glib.Device.Coroutine;

export namespace gl::window
{
	class [[nodiscard]] ManagedWindow
		: public ::std::enable_shared_from_this<ManagedWindow>
	{
	public:
		Window underlying;
	};
}
