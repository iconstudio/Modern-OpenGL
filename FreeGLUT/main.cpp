#include "pch.hpp"
#include "Internal.hpp"
#undef CreateWindow
#undef CreateWindowEx

import Glib;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Device.Window;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_DESTROY: return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const auto& my_windows_class = L"MY_CLASS";

int main(const int& argc, char** argv)
{
	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	auto hinstance = gl::device::GetProcessInstance();

	auto property = gl::device::WindowProperty{ hinstance, WndProc, my_windows_class };

	property.Register();

	auto window = gl::device::CreateWindow(property, L"MY_TITLE", -1, -1, 400, 300);

	window.Awake();
	window.Start();

	while (true)
	{

	}

	return 0;
}
