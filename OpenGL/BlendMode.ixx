export module Glib.Blender:Mode;
import :Option;

namespace gl
{
	struct DstBlendOption;
	struct SrcBlendOption;

	struct [[nodiscard]] DstBlendOption
	{
	public:
		constexpr operator BlendOption() const noexcept
		{
			return myOption;
		}

		[[nodiscard]]
		constexpr bool operator==(const DstBlendOption& other) noexcept
		{
			return other.myOption == myOption;
		}

		bool operator==(const SrcBlendOption&) = delete;

		BlendOption myOption;
	};

	struct [[nodiscard]] SrcBlendOption
	{
	public:
		constexpr operator BlendOption() const noexcept
		{
			return myOption;
		}

		[[nodiscard]]
		constexpr bool operator==(const SrcBlendOption& other) noexcept
		{
			return other.myOption == myOption;
		}

		bool operator==(const DstBlendOption&) = delete;

		BlendOption myOption;
	};
}

export namespace gl
{
	namespace blend_options
	{
		inline constexpr DstBlendOption DstZero{ BlendOption::Zero };
		inline constexpr DstBlendOption DstOne{ BlendOption::One };
		inline constexpr DstBlendOption DstFromSrcColor{ BlendOption::SourceColour };
		inline constexpr DstBlendOption DstFromSrcAlpha{ BlendOption::SourceAlpha };
		inline constexpr DstBlendOption DstFromInvertedSrcColor{ BlendOption::InvertedSrcColour };
		inline constexpr DstBlendOption DstFromInvertedSrcAlpha{ BlendOption::InvertedSrcAlpha };
		inline constexpr DstBlendOption DstFromMyAlpha{ BlendOption::DestAlpha };
		inline constexpr DstBlendOption DstFromInvertedMyAlpha{ BlendOption::InvertedDstAlpha };

		inline constexpr SrcBlendOption SrcZero{ BlendOption::Zero };
		inline constexpr SrcBlendOption SrcOne{ BlendOption::One };
		inline constexpr SrcBlendOption SrcFromDstColor{ BlendOption::DestColour };
		inline constexpr SrcBlendOption SrcFromDstAlpha{ BlendOption::DestAlpha };
		inline constexpr SrcBlendOption SrcFromInvertedDstColor{ BlendOption::InvertedDstColour };
		inline constexpr SrcBlendOption SrcFromInvertedDstAlpha{ BlendOption::InvertedDstAlpha };
		inline constexpr SrcBlendOption SrcFromMyAlpha{ BlendOption::SourceAlpha };
		inline constexpr SrcBlendOption SrcFromInvertedMyAlpha{ BlendOption::InvertedSrcAlpha };
		inline constexpr SrcBlendOption SrcFromSaturation{ BlendOption::SaturateSourceAlpha };
	}

	struct [[nodiscard]] BlendMode
	{
		BlendOption dstOption;
		BlendOption srcOption;
	};
}
