export module Glib:Primitive;
import <cstdint>;
import <span>;
import Glib.Windows.Colour;

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

	namespace draw
	{
		using ::gl::win32::Colour;

		void Vertex(int x, int y, int z) noexcept;
		void Vertex(float x, float y, float z) noexcept;
		void Vertex(double x, double y, double z) noexcept;
		void Vertex(std::span<int, 3> list) noexcept;
		void Vertex(std::span<float, 3> list) noexcept;
		void Vertex(std::span<double, 3> list) noexcept;

		void Normal(int x, int y, int z) noexcept;
		void Normal(float x, float y, float z) noexcept;
		void Normal(double x, double y, double z) noexcept;
		void Normal(std::span<int, 3> list) noexcept;
		void Normal(std::span<float, 3> list) noexcept;
		void Normal(std::span<double, 3> list) noexcept;

		void TexCoord(int s, int t) noexcept;
		void TexCoord(float s, float t) noexcept;
		void TexCoord(double s, double t) noexcept;
		void TexCoord(std::span<int, 2> list) noexcept;
		void TexCoord(std::span<float, 2> list) noexcept;
		void TexCoord(std::span<double, 2> list) noexcept;

		void SetColour(const Colour& color) noexcept;
		void SetColour(Colour&& color) noexcept;
		void SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b) noexcept;
		void SetColour(int r, int g, int b) noexcept;
		void SetColour(float ratio_r, float ratio_g, float ratio_b) noexcept;
		void SetColour(double ratio_r, double ratio_g, double ratio_b) noexcept;
		void SetColour(int r, int g, int b, int a) noexcept;
		void SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) noexcept;
		void SetColour(float ratio_r, float ratio_g, float ratio_b, float ratio_a) noexcept;
		void SetColour(double ratio_r, double ratio_g, double ratio_b, double ratio_a) noexcept;
	}
}
