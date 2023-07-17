export module Glib.Blender;
import Glib;

export namespace gl
{
	enum class [[nodiscard]] BlendMode : unsigned int
	{
		None = 0x0000,
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
		Blender(bool enable) noexcept;
		Blender(BlendMode src, BlendMode dest) noexcept;
		~Blender() noexcept;

		Blender(const Blender&) = delete;
		constexpr Blender(Blender&&) noexcept = default;
		Blender& operator=(const Blender&) = delete;
		constexpr Blender& operator=(Blender&&) noexcept = default;

	private:
		bool isBlending = false;
		bool wasBlending = false;

		// My modes, not current modes
		BlendMode mySrcMode, myDestMode;
		// Stacked modes
		BlendMode prevSrcMode = BlendMode::None, prevDestMode = BlendMode::None;
		// Optional
		BlendFunction prevFunc;
	};
}
