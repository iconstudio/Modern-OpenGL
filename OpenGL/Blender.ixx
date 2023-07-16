export module Glib.Blender;
import Glib;

export namespace gl
{
	enum class [[nodiscard]] BlendMode : unsigned int
	{
		One = 0x0001,
	};

	enum class [[nodiscard]] BlendFunction : unsigned int
	{
		Add = 0x8006,
	};

	enum class [[nodiscard]] BlendTarget : unsigned int
	{
		Dest = 0x0BE0,
		Source = 0x0BE1,
	};

	class Blender
	{
	public:
		constexpr Blender() noexcept = default;
		constexpr ~Blender() noexcept = default;

		Blender(const Blender&) = delete;
		constexpr Blender(Blender&&) noexcept = default;
		Blender& operator=(const Blender&) = delete;
		constexpr Blender& operator=(Blender&&) noexcept = default;



		constexpr Blender(const Blender&) noexcept = default;
		constexpr Blender& operator=(const Blender&) noexcept = default;
		constexpr Blender(Blender&&) noexcept = default;
		constexpr Blender& operator=(Blender&&) noexcept = default;
	};
}
