export module Glib.Framework;
import <memory>;
import <functional>;
import <string_view>;
export import Glib;
export import Glib.Rect;
import Glib.Windows.Definitions;
import Glib.Windows.ManagedClient;
export import Glib.Windows.Event;

export namespace gl
{
	using gl::win32::FilePath;
	using gl::win32::Colour;
	using gl::win32::EventID;
	using gl::win32::GraphicDeviceContext;
	using gl::win32::RenderEventHandler;
	using gl::win32::ManagedWindow;
	// TODO: std::function -> std::copyable_function
	using RenderDelegate = std::function<void()>;

	namespace framework
	{
		void DefaultRenderer() noexcept;

		struct [[nodiscard]] Descriptor
		{
			gl::system::Descriptor glDescriptor;
			std::wstring_view title;
			int wx, wy, ww, wh;

			RenderDelegate renderer = DefaultRenderer;
			int minW = 60, minH = 60;
			bool isResizable = true;
			bool isPowersave = false;
		};

		enum class InitError
		{
			Success,
			FailedOnCreatingSystem,
			FailedOnCreatingWindow,
			FailedOnSettingPixelFormat,
			FailedOnStartup,
		};

		[[nodiscard]]
		Descriptor MakeDefaultDescriptor() noexcept;
	}

	/// <summary>
	/// Client Interface With OpenGL
	/// </summary>
	class [[nodiscard]] Framework : public std::enable_shared_from_this<Framework>
	{
	public:
		using base = std::enable_shared_from_this<Framework>;
		using handle_t = gl::win32::ManagedWindow;
		using event_handler_t = handle_t::event_handler_t;
		using opengl_system_t = std::shared_ptr<gl::System>;

		constexpr Framework() noexcept = default;
		~Framework() noexcept = default;

		framework::InitError Initialize(const framework::Descriptor& setup);
		framework::InitError Initialize();
		void Run() noexcept;

		void AddEventHandler(EventID id, const event_handler_t& procedure) noexcept;
		void AddEventHandler(EventID id, event_handler_t&& procedure) noexcept;
		void RemoveEventHandler(EventID id) noexcept;

		void SetRenderer(RenderDelegate handler) noexcept;

		[[nodiscard]] handle_t& GetHandle() noexcept;
		[[nodiscard]] const handle_t& GetHandle() const noexcept;

		[[nodiscard]] friend std::shared_ptr<Framework> CreateFramework() noexcept;

	private:
		std::unique_ptr<handle_t> myInstance{ nullptr };
		gl::Rect window_rect{};

		opengl_system_t glSystem{ nullptr };
	};

	[[nodiscard]] std::shared_ptr<Framework> CreateFramework() noexcept;
}
