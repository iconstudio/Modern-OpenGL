export module Glib.Blender;
import Utility.Monad;

export namespace gl
{
	enum class [[nodiscard]] BlendMode : unsigned int
	{
		None = 0x0000,
		One = 0x0001,
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

		[[nodiscard]] bool IsBlending() const noexcept;
		[[nodiscard]] util::Monad<BlendMode> GetSrcMode() const noexcept;
		[[nodiscard]] util::Monad<BlendMode> GetDstMode() const noexcept;
		[[nodiscard]] util::Monad<BlendMode> GetPrevSrcMode() const noexcept;
		[[nodiscard]] util::Monad<BlendMode> GetPrevDstMode() const noexcept;

		void swap(Blender& other) noexcept;

		Blender(const Blender&) = delete;
		constexpr Blender(Blender&&) noexcept = default;
		Blender& operator=(const Blender&) = delete;
		constexpr Blender& operator=(Blender&&) noexcept = default;

	private:
		bool isBlending = false;
		bool wasBlending = false;

		// [Optional] My modes, not current modes
		BlendMode mySrcMode, myDstMode;
		// [Optional] Stacked previous modes
		BlendMode prevSrcMode = BlendMode::None, prevDstMode = BlendMode::None;
	};
}
