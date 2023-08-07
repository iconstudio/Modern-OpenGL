export module Glib.Blender;
import <cstdint>;
import :Option;
import :Mode;

export namespace gl
{
	enum class [[nodiscard]] BlendTarget : std::uint32_t
	{
		Dest = 0x0BE0U,
		Source = 0x0BE1U,
	};

	class Blender
	{
	public:
		Blender(bool enable) noexcept;
		Blender(const BlendMode& mode) noexcept;
		Blender(BlendMode&& mode) noexcept;
		Blender(BlendOption src, BlendOption dest) noexcept;
		~Blender() noexcept;

		void Apply() const noexcept;

		[[nodiscard]] bool IsBlending() const noexcept;
		[[nodiscard]] BlendOption GetSrcMode() const noexcept;
		[[nodiscard]] BlendOption GetDstMode() const noexcept;
		[[nodiscard]] BlendOption GetPrevSrcMode() const noexcept;
		[[nodiscard]] BlendOption GetPrevDstMode() const noexcept;

		void swap(Blender& other) noexcept;

		Blender(const Blender&) = delete;
		Blender(Blender&&) noexcept = default;
		Blender& operator=(const Blender&) = delete;
		Blender& operator=(Blender&&) noexcept = default;

	private:
		bool isBlending = false;
		bool wasBlending = false;

		// [Optional] My modes, not actually current modes
		BlendMode myMode{ BlendOption::Invalid, BlendOption::Invalid };
		// [Optional] Stacked previous modes
		BlendMode prevMove{ BlendOption::Invalid, BlendOption::Invalid };
	};
}
