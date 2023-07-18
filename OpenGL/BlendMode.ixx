export module Glib.Blender:Mode;

export namespace gl
{
	enum class [[nodiscard]] BlendOption : unsigned int
	{
		Invalid = static_cast<unsigned int>(-1),
		Zero = 0x0000,
		One = 0x0001,
		SourceColour = 0x0300,
		InvertedSrcColour = 0x0301,
		SourceAlpha = 0x0302,
		InvertedSrcAlpha = 0x0303,
		DestColour = 0x0306,
		InvertedDstColour = 0x0307,
		DestAlpha = 0x0304,
		InvertedDstAlpha = 0x0305,
		SaturateSourceAlpha = 0x0308
	};
}

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

		constexpr bool operator==(DstBlendOption) noexcept = default;
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

		constexpr bool operator==(SrcBlendOption) noexcept = default;
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
