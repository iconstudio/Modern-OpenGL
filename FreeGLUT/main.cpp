#include "pch.hpp"

import Glib;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Device.Window;

int main(const int& argc, char** argv)
{
	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	auto hinstance = gl::device::GetProcessInstance();
	//uto window = gl::device::ManagedHandle::Create(hinstance, L"class", L"title", 0U, -1, -1, 400, 300);


	while (true)
	{

	}

	return 0;
}
