module;
module Glib;
import Utility;
import Utility.Print;
import Utility.FixedString;
import Glib.Rect;
import Glib.Device.Colour;
import Glib.Display;

static inline int window_handle = -1;
static inline gl::DisplayModes window_mode{};
static inline gl::Rect window_rect{};

std::shared_ptr<gl::Framework>
gl::CreateFramework()
noexcept
{
	return std::shared_ptr<Framework>();
}

void gl::Initialize(const DisplayModes& mode, const int& x, const int& y, const int& w, const int& h) noexcept
{
	display::dpi::SetDPIAware(true);

	window_rect.x = x;
	window_rect.y = y;
	window_rect.w = w;
	window_rect.h = h;
	window_mode = mode;
}

void gl::Initialize(const DisplayModes& mode, default_position_t, const int& w, const int& h) noexcept
{
	return Initialize(mode, 400, 400, w, h);
}

void gl::Initialize(const DisplayModes& mode, const int& x, const int& y, default_resoulution_t) noexcept
{
	return Initialize(mode, x, y, default_window_w, default_window_h);
}

void gl::Initialize(const DisplayModes& mode, const int& w, const int& h) noexcept
{
	return Initialize(mode, 400, 400, w, h);
}

void gl::Initialize(const DisplayModes& mode, default_position_t, default_resoulution_t) noexcept
{
	return Initialize(mode, 400, 400, default_window_w, default_window_h);
}

void gl::Start()
{
	if (display::IsDimmingMode())
	{
		util::Println("Dark Mode");
	}
	else
	{
		util::Println("Light Mode");
	}
}
