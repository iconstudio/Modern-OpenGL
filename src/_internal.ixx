export module Glut.Internal;
export import <cstdlib>;
export import <cstring>;
export import <cmath>;
export import <ctime>;
export import <numbers>;

export namespace gl::detail
{
	template<typename T = int>
	inline constexpr T INVALID_MODIFIERS = static_cast<T>(0xFFFFFFFFU);
}
