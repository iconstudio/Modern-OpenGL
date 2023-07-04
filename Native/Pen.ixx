module;
#include "Internal.hpp"

export module Glib.Device.Pen;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	enum class [[nodiscard]] PenStyles
	{
		None = 5,// PS_NULL
		Fill = 0, // PS_SOLID
		Dash = 1, // PS_DASH
		Dots = 2, // PS_DOT
		DashDot = 3, // PS_DASHDOT
		//Frame = 6, // PS_INSIDEFRAME
	};

	class [[nodiscard]] Pen
	{
	public:
	};
}
