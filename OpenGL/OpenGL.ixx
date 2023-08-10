export module Glib;
import <string>;
import <string_view>;
import <cstdint>;
export import :Pixel;
export import :TransformState;
export import :Transform;
export import :Comparator;
export import :State;
export import :ClearBits;
export import :Primitive;
export import :BlendMode;
export import :BlendOption;
export import :Blender;
export import :Object;
export import :BufferType;
export import :BufferUsage;
export import :BufferLayout;
export import :BufferObject;
export import :VertexBuffer;
export import :IndexBuffer;
export import :SharedBufferObject;
export import :UniqueBufferObject;
export import :System;
export import Glib.Windows.Colour;

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

export namespace gl::global
{
	using ::gl::win32::Colour;

	void SetState(const gl::State& state) noexcept;
	void SetState(const volatile gl::State& state) noexcept;
	void SetState(gl::State&& state) noexcept;
	void SetState(volatile gl::State&& state) noexcept;
	void SetState(const gl::State& state, bool flag) noexcept;
	void SetState(const volatile gl::State& state, bool flag) noexcept;
	void SetState(gl::State&& state, bool flag) noexcept;
	void SetState(volatile gl::State&& state, bool flag) noexcept;

	void SetBackgroundColour(const Colour& colour) noexcept;
	void SetBackgroundColour(Colour&& colour) noexcept;
	void SetBackgroundColour(const std::uint8_t& r, const std::uint8_t& g, const std::uint8_t& b, const std::uint8_t& a = 0xFFU) noexcept;

	void Clear(Clearance target) noexcept;

	void SetViewport(const std::int32_t& x, const std::int32_t& y, const std::uint32_t& width, const std::uint32_t& height) noexcept;
	void SetViewport(std::int32_t&& x, std::int32_t&& y, std::uint32_t&& width, std::uint32_t&& height) noexcept;

	[[nodiscard]] bool IsBlending() noexcept;
	[[nodiscard]] bool IsCulling() noexcept;
	[[nodiscard]] bool IsScissoring() noexcept;
	[[nodiscard]] bool IsTestingAlpha() noexcept;
	[[nodiscard]] bool IsTestingDepth() noexcept;
	[[nodiscard]] bool IsTestingStencil() noexcept;
}
