module;
#include "stdafx.inl"
#include <windows.ui.viewmanagement.h>

export module Glib;
export import Utility.FixedString;
export import Glib.DisplayModes;
import Glib.Window.ManagedWindow;

export namespace gl
{
	EXT_C struct [[nodiscard]] default_position_t { constexpr default_position_t() noexcept = default; };
	EXT_C struct [[nodiscard]] default_resoulution_t { constexpr default_resoulution_t() noexcept = default; };

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

	void Start()
	{
		using ABI::Windows::System::VirtualKey_Snapshot;

		auto settings = UISettings();

		auto foreground = settings.GetColorValue(UIColorType::Foreground);
	}
}
