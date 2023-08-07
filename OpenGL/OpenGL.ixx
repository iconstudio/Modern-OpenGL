export module Glib;
import <string>;
import <string_view>;
export import :Utility;
export import :Pixel;
export import :TransformState;
export import :Transform;
export import :Comparator;
export import :State;
export import :Primitive;
export import :Object;
export import :BufferObject;
export import :BufferLayout;
export import :System;

export namespace gl::info
{
	[[nodiscard]]
	std::string_view GetVersion() noexcept;

	[[nodiscard]]
	std::string_view GetVendor() noexcept;

	[[nodiscard]]
	std::string_view GetRenderer() noexcept;

	[[nodiscard]]
	std::string_view GetExtensions() noexcept;

	[[nodiscard]]
	std::string_view GetShadingLanguageVersion() noexcept;
}
