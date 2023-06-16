module;
module Glut;
import Glut.Rect;

inline static int window_handle = -1;
inline static glut::DisplayModes window_mode{};
inline static glut::Rect window_rect{};
inline static glut::DisplayModes window_mode{};

void glut::Initialize(const DisplayModes& mode, const int& x, const int& y, const int& w, const int& h) noexcept
{
	window_rect.x = x;
	window_rect.y = y;
	window_rect.w = w;
	window_rect.h = h;
	window_mode = mode;

	glutInitDisplayMode(static_cast<unsigned int>(mode));
	glutInitWindowPosition(x, y);
	glutInitWindowSize(w, h);
	glutCreateWindow("OpenGL");
}

void glut::Initialize(const DisplayModes& mode, default_position_t, const int& w, const int& h) noexcept
{
	return Initialize(mode, default_window_x, default_window_y, w, h);
}

void glut::Initialize(const DisplayModes& mode, const int& x, const int& y, default_resoulution_t) noexcept
{
	return Initialize(mode, x, y, default_window_w, default_window_h);
}

void glut::Initialize(const DisplayModes& mode, const int& w, const int& h) noexcept
{
	return Initialize(mode, default_window_x, default_window_y, w, h);
}

void glut::Initialize(const DisplayModes& mode, default_position_t, default_resoulution_t) noexcept
{
	return Initialize(mode, default_window_x, default_window_y, default_window_w, default_window_h);
}
