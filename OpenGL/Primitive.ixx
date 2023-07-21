export module Glib:Primitive;

export namespace gl
{
	enum class [[nodiscard]] Primitive : unsigned int
	{
		Points = 0x0000,
		Lines = 0x0001,
		LineLoop = 0x0002,
		LineStrip = 0x0003,
		Triangles = 0x0004,
		TriangleStrip = 0x0005,
		TriangleFan = 0x0006,
		Quads = 0x0007,
		QuadStrip = 0x0008,
		Polygon = 0x0009,
	};

	namespace primitive
	{
		class [[nodiscard]] Context
		{
		public:
			Context(Primitive mode) noexcept;
			~Context() noexcept;

			Context(const Context&) = delete;
			Context& operator=(const Context&) = delete;
			Context(Context&& other) = delete;
			Context& operator=(Context&& other) = delete;
		};
	}

	namespace global
	{
		void BeginPrimitives(Primitive mode) noexcept;
		void EndPrimitives() noexcept;
	}
}
