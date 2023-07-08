module;
module Glib;
import Utility;
import Utility.Print;
import Utility.FixedString;
import Glib.Rect;
import Glib.Device.Colour;

static inline int window_handle = -1;
static inline gl::DisplayModes window_mode{};

std::shared_ptr<gl::Framework>
gl::InitializeFramework()
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
