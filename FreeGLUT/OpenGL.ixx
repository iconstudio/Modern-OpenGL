export module Glib;
import <memory>;
import Glib.Window.ManagedWindow;
export import Glib:DisplayModes;
import Glib:DefaultProperty;

export namespace gl
{
	constexpr default_position_t default_position{};
	constexpr default_resoulution_t default_resoulution{};

	constexpr int default_window_x = -1;
	constexpr int default_window_y = -1;
	constexpr int default_window_w = 800;
	constexpr int default_window_h = 600;

	void Initialize(const DisplayModes& mode, const int& x, const int& y, const int& w, const int& h) noexcept;
	void Initialize(const DisplayModes& mode, default_position_t, const int& w, const int& h) noexcept;
	void Initialize(const DisplayModes& mode, const int& x, const int& y, default_resoulution_t) noexcept;
	void Initialize(const DisplayModes& mode, const int& w, const int& h) noexcept;
	void Initialize(const DisplayModes& mode, default_position_t, default_resoulution_t) noexcept;

	void Start();
}
