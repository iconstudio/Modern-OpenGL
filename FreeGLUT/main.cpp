#include "pch.hpp"

import Glib;

int main(const int& argc, char** argv)
{
	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	return 0;
}
