#include "pch.hpp"
#include "Internal.hpp"

import Glib;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Device.Window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

const auto& my_windows_class = L"MY_CLASS";

int main(const int& argc, char** argv)
{
	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	auto hinstance = gl::device::GetProcessInstance();
	const int error0 = gl::device::GetLastError();


	auto property = gl::device::DeviceProperty{ hinstance, WndProc, my_windows_class };
	const int error1 = gl::device::GetLastError();

	property.Register();
	const int error2 = gl::device::GetLastError();

	auto window = gl::device::Window::Create(property, L"MY_TITLE", -1, -1, 400, 300);
	const int error3 = gl::device::GetLastError();

	window.Show();
	const int error4 = gl::device::GetLastError();

	//while (true)
	{

	}

	return 0;
}
