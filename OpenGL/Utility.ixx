export module Glib:Utility;
import <cstdint>;
export import :State;
export import :ClearBits;
import Glib.Windows.Colour;

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
