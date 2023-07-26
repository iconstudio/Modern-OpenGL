export module Glib.Legacy.Fog;
import <cstdint>;
import Glib;
import Glib.Windows.Colour;

export namespace gl::legacy
{
	using ::gl::win32::Colour;

	enum [[nodiscard]] FogOperation
	{
		Linear = 0x2601,
		Exp1 = 0x0800,
		Exp2 = 0x0801,
	};

	class Fog
	{
	public:
		Fog(float near, float far, float density = 1.0) noexcept;
		Fog(FogOperation operation, float near, float far, float density = 1.0) noexcept;
		Fog(const Colour& color, float near, float far, float density = 1.0) noexcept;
		Fog(Colour&& color, float near, float far, float density = 1.0) noexcept;
		Fog(FogOperation operation, const Colour& color, float near, float far, float density = 1.0) noexcept;
		Fog(FogOperation operation, Colour&& color, float near, float far, float density = 1.0) noexcept;
		~Fog() noexcept;

		void Operation(FogOperation operation) noexcept;
		[[nodiscard]] FogOperation Operation() const noexcept;

		void Color(const Colour& color) noexcept;
		void Color(Colour&& color) noexcept;
		void Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 0xFFU) noexcept;
		void Color(float r, float g, float b, float a = 1.0f) noexcept;
		[[nodiscard]] const Colour& Color() const noexcept;

		void Density(float density) noexcept;
		[[nodiscard]] float Density() const noexcept;

		void NearDistance(float dist) noexcept;
		[[nodiscard]] float NearDistance() const noexcept;

		void FarDistance(float dist) noexcept;
		[[nodiscard]] float FarDistance() const noexcept;

		Fog(const Fog&) noexcept = delete;
		Fog(Fog&&) noexcept = delete;
		Fog& operator=(const Fog&) noexcept = delete;
		Fog& operator=(Fog&&) noexcept = delete;

	private:
		FogOperation myOperation;
		Colour myColor{};
		float cachedColor[4]{};
		float myDensity{ 1.0f };
		float distNear{}, distFar{ 100.0f };
	};
}
