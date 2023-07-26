export module Glib.Legacy.Primitive;
import <cstdint>;
import <span>;
import Glib;

export namespace gl::legacy
{
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

		void Begin(Primitive mode) noexcept;
		void End() noexcept;

		void Vertex(std::int32_t x, std::int32_t y, std::int32_t z) noexcept;
		void Vertex(float x, float y, float z) noexcept;
		void Vertex(double x, double y, double z) noexcept;
		void Vertex(std::span<std::int32_t, 3> list) noexcept;
		void Vertex(std::span<float, 3> list) noexcept;
		void Vertex(std::span<double, 3> list) noexcept;

		void Normal(std::int32_t x, std::int32_t y, std::int32_t z) noexcept;
		void Normal(float x, float y, float z) noexcept;
		void Normal(double x, double y, double z) noexcept;
		void Normal(std::span<std::int32_t, 3> list) noexcept;
		void Normal(std::span<float, 3> list) noexcept;
		void Normal(std::span<double, 3> list) noexcept;

		void TexCoord(std::int32_t s, std::int32_t t) noexcept;
		void TexCoord(float s, float t) noexcept;
		void TexCoord(double s, double t) noexcept;
		void TexCoord(std::span<std::int32_t, 2> list) noexcept;
		void TexCoord(std::span<float, 2> list) noexcept;
		void TexCoord(std::span<double, 2> list) noexcept;

		void SetColour(const Colour& color) noexcept;
		void SetColour(Colour&& color) noexcept;
		void SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b) noexcept;
		void SetColour(std::int32_t r, std::int32_t g, std::int32_t b) noexcept;
		void SetColour(float ratio_r, float ratio_g, float ratio_b) noexcept;
		void SetColour(double ratio_r, double ratio_g, double ratio_b) noexcept;
		void SetColour(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a) noexcept;
		void SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) noexcept;
		void SetColour(float ratio_r, float ratio_g, float ratio_b, float ratio_a) noexcept;
		void SetColour(double ratio_r, double ratio_g, double ratio_b, double ratio_a) noexcept;
	}
}
