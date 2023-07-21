export module Glib:TransformState;

export namespace gl
{
	enum class [[nodiscard]] TransformMode : unsigned int
	{
		None = 0x0000,
		ModelView = 0x1700,
		Projection = 0x1701,
		Texture = 0x1702,
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
