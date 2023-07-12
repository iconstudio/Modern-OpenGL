export module Glib.Framework;
import <memory>;
import <string_view>;
import Glib.Rect;
import Glib.GraphicContext;
import Glib.Window.ManagedWindow;

export namespace gl
{
	namespace framework
	{
		struct Descriptor
		{
			std::wstring_view title;
			int wx, wy, ww, wh;
			bool isPowersave = false;
		};

		enum class InitError
		{
			Success,
			FailedOnCreatingWindow,
			FailedOnSettingPixelFormat,
		};

		[[nodiscard]]
		consteval Descriptor MakeDefaultDescriptor() noexcept
		{
			return Descriptor
			{
				.title = L"FreeGLUT",
				.wx = static_cast<int>(0x80000000), // CW_USEDEFAULT
				.wy = 0,
				.ww = 800,
				.wh = 600
			};
		}

		inline constexpr Descriptor DefaultDescriptor = MakeDefaultDescriptor();
	}

	class [[nodiscard]] Framework : public std::enable_shared_from_this<Framework>
	{
	public:
		using base = std::enable_shared_from_this<Framework>;
		using handle_t = gl::window::ManagedWindow;
		using renderer_t = gl::window::RenderEventHandler;

		constexpr Framework() noexcept = default;
		~Framework() noexcept = default;

		framework::InitError Initialize(const framework::Descriptor& setup);
		framework::InitError Initialize(framework::Descriptor&& setup);
		framework::InitError Initialize();
		void Run() noexcept;

		void AddEventHandler(handle_t::event_id_t id, const handle_t::event_handler_t& procedure) noexcept;
		void AddEventHandler(handle_t::event_id_t id, handle_t::event_handler_t&& procedure) noexcept;
		void RemoveEventHandler(handle_t::event_id_t id) noexcept;

		void SetRenderer(renderer_t handler) noexcept;

	private:
		std::unique_ptr<handle_t> myInstance{ nullptr };
		gl::Rect window_rect{};
		GLContext myHandle{};
	};
}
