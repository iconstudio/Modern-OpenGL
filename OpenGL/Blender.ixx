export module Glib.Blender;
import Utility.Monad;

export namespace gl
{
	enum class [[nodiscard]] BlendOption : unsigned int
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
		Blender(BlendOption src, BlendOption dest) noexcept;
		~Blender() noexcept;

		[[nodiscard]] bool IsBlending() const noexcept;
		[[nodiscard]] util::Monad<BlendOption> GetSrcMode() const noexcept;
		[[nodiscard]] util::Monad<BlendOption> GetDstMode() const noexcept;
		[[nodiscard]] util::Monad<BlendOption> GetPrevSrcMode() const noexcept;
		[[nodiscard]] util::Monad<BlendOption> GetPrevDstMode() const noexcept;

		void swap(Blender& other) noexcept;

		Blender(const Blender&) = delete;
		constexpr Blender(Blender&&) noexcept = default;
		Blender& operator=(const Blender&) = delete;
		constexpr Blender& operator=(Blender&&) noexcept = default;

	private:
		bool isBlending = false;
		bool wasBlending = false;

		// [Optional] My modes, not current modes
		BlendOption mySrcMode = BlendOption::None, myDstMode = BlendOption::None;
		// [Optional] Stacked previous modes
		BlendOption prevSrcMode = BlendOption::None, prevDstMode = BlendOption::None;
	};
}
