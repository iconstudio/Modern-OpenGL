export module Glib:BlendMode;
import :BlendOption;

export namespace gl
{
	struct [[nodiscard]] BlendMode
	{
		BlendOption srcOption;
		BlendOption dstOption;
	};

	inline constexpr BlendMode DefaultAlpha{ BlendOption::SourceAlpha, BlendOption::InvertedSrcAlpha };
	inline constexpr BlendMode Opaque{ BlendOption::One, BlendOption::Zero };
}
