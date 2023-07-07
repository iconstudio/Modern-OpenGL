export module Glib:Framework;
import <memory>;
import Glib.Window.ManagedWindow;

export namespace gl
{
	class Framework
	{
	public:
		Framework();
		~Framework();

	private:
		std::unique_ptr<window::ManagedWindow> myInstance;
	};
}
