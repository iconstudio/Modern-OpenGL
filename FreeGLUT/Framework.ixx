export module Glib:Framework;
import <memory>;
import Glib.Window.ManagedWindow;
import :DisplayModes;

export namespace gl
{
	class Framework : std::enable_shared_from_this<Framework>
	{
	public:
		using base = std::enable_shared_from_this<Framework>;

		Framework();
		~Framework();

	private:
		std::unique_ptr<window::ManagedWindow> myInstance;
		DisplayModes displayMode;
	};
}
