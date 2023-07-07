export module Glib:Framework;
import <memory>;
import Glib.Window.ManagedWindow;
import :DisplayModes;

export namespace gl
{
	namespace framework
	{
		enum class [[nodiscard]] InitError
		{

		};
	}

	class Framework : std::enable_shared_from_this<Framework>
	{
	public:
		using base = std::enable_shared_from_this<Framework>;

		Framework();
		~Framework();

		framework::InitError Initialize(const int& x, const int& y, const int& width, const int& height);
		void Run();

	private:
		std::unique_ptr<window::ManagedWindow> myInstance;
		DisplayModes displayMode;
	};
}
