export module Glib.Framework;
import <memory>;
import Glib.Window.Factory;
import Glib.Window.ManagedWindow;

export namespace gl
{
	namespace framework
	{
		enum class [[nodiscard]] InitError
		{

		};
	}

	class [[nodiscard]] Framework : public std::enable_shared_from_this<Framework>
	{
	public:
		using base = std::enable_shared_from_this<Framework>;

		Framework() noexcept;
		~Framework() noexcept;

		framework::InitError Initialize(const int& x, const int& y, const int& width, const int& height);
		void Run() noexcept;

	private:
		std::unique_ptr<window::ManagedWindow> myInstance;
	};
}
