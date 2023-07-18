export module Glib.Blender:Mode;

export namespace gl
{
	enum class [[nodiscard]] BlendOption : unsigned int
	{
		Invalid = static_cast<unsigned int>(-1),
		Zero = 0x0000,
		One = 0x0001,
	};
}

namespace gl
{
	class [[nodiscard]] DestBlendOption
	{
	public:
		constexpr operator BlendOption() const noexcept
		{
			return myOption;
		}

		BlendOption myOption;
	};

	class [[nodiscard]] SrcBlendOption
	{
	public:
		constexpr operator BlendOption() const noexcept
		{
			return myOption;
		}

		BlendOption myOption;
	};
}

export namespace gl
{
	class [[nodiscard]] BlendMode
	{
	public:
		BlendOption myOption;
	};
}
