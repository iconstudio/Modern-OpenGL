export module Glib.Blender:Mode;
import :Option;

export namespace gl
{
	struct [[nodiscard]] BlendMode
	{
		BlendOption dstOption;
		BlendOption srcOption;
	};
}
