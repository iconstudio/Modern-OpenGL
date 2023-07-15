export module Glib.Blender;
import Glib;

export namespace gl
{
	class Blender
	{
	public:
		constexpr Blender() noexcept = default;
		constexpr ~Blender() noexcept = default;




		constexpr Blender(const Blender&) noexcept = default;
		constexpr Blender& operator=(const Blender&) noexcept = default;
		constexpr Blender(Blender&&) noexcept = default;
		constexpr Blender& operator=(Blender&&) noexcept = default;
	};
}
