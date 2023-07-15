export module Glib:Utility;
import <cstdint>;
import Glib.Windows.Colour;
export import :State;

export namespace gl
{
	using win32::Colour;
}

export namespace gl::global
{
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
}
