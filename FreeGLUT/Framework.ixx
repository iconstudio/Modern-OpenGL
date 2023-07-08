export module Glib.Framework;
import <memory>;
import <string>;
import Glib.Rect;
import Glib.Window.ManagedWindow;

export namespace gl
{
	namespace framework
	{
		struct Descriptor
		{
			std::wstring title;
			int wx, wy, ww, wh;
		};

		enum class [[nodiscard]] InitError
		{
			Success,
			FailedOnCreatingWindow,
		};
	}

	class [[nodiscard]] Framework : public std::enable_shared_from_this<Framework>
	{
	public:
		using base = std::enable_shared_from_this<Framework>;

		Framework() noexcept;
		~Framework() noexcept;

		framework::InitError Initialize(const framework::Descriptor& setup);
		void Run() noexcept;

	private:
		std::unique_ptr<window::ManagedWindow> myInstance{ nullptr };
		gl::Rect window_rect{};
	};
}
