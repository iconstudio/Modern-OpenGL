export module Glib:TransformState;
import <cstdint>;

export namespace gl
{
	enum class [[nodiscard]] TransformMode : std::uint32_t
	{
		None = 0x0000U,
		ModelView = 0x1700U,
		Projection = 0x1701U,
		Texture = 0x1702U,
	};

	namespace transform
	{
		void SetState(TransformMode mode) noexcept;
		void PushState() noexcept;
		void PopState() noexcept;

		class Context
		{
		public:
			Context() noexcept;
			Context(TransformMode mode) noexcept;
			~Context() noexcept;

			Context(const Context&) = delete;
			Context& operator=(const Context&) = delete;
			Context(Context&& other) = delete;
			Context& operator=(Context&& other) = delete;
		};
	}
}
