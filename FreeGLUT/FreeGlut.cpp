module;
module Glut;

void glut::Initialize(const DisplayModes& mode, const int& x, const int& y, const int& w, const int& h) noexcept
{

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
