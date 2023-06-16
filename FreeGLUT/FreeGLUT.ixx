module;
#include "stdafx.inl"

export module Glut;
export import Glut.DisplayModes;

export namespace glut
{
	struct default_position_t { constexpr default_position_t() noexcept = default; };
	struct default_resoulution_t { constexpr default_resoulution_t() noexcept = default; };

	constexpr default_position_t default_position{};
	constexpr default_resoulution_t default_resoulution{};

	void Initialize(const DisplayModes& mode, const int& x, const int& y, const int& w, const int& h) noexcept;
	void Initialize(const DisplayModes& mode, default_position_t, const int& w, const int& h) noexcept;
	void Initialize(const DisplayModes& mode, const int& x, const int& y, default_resoulution_t) noexcept;
	void Initialize(const DisplayModes& mode, default_position_t, default_resoulution_t) noexcept;
}
