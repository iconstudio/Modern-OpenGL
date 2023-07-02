module;
#include "Internal.hpp"

export module Glib.Window:ABI;
import <string_view>;
import Glib.DefaultProperty;

export namespace gl::window::detail
{
	inline constexpr default_property_t<int> use_default = default_property_t{ CW_USEDEFAULT };

}
