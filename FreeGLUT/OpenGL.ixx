export module Glib;
import <memory>;
import :DefaultProperty;
export import :DisplayModes;
export import Glib.Framework;

export namespace gl
{
	constexpr default_position_t default_position{};
	constexpr default_resoulution_t default_resoulution{};

	constexpr int default_window_w = 800;
	constexpr int default_window_h = 600;

	std::shared_ptr<Framework> InitializeFramework() noexcept;
}
