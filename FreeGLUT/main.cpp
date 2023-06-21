#include "pch.hpp"
#include "Internal.hpp"
#undef CreateWindow
#undef CreateWindowEx

import Utility.Concurrency.Thread;
import Glib;
import Glib.Device.ProcessInstance;
import Glib.Device.Handle;
import Glib.Window;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		// Started by WM_DESTROY
		case WM_QUIT:
		{
			//KillTimer(hwnd, RENDER_TIMER_ID);
		}
		break;

		// Started by close button or system menu or Alt+F4
		case WM_CLOSE:
		{
			::DestroyWindow(hwnd);
		}
		break;

		// Started by DestroyWindow
		case WM_DESTROY:
		{
			gl::window::PostQuitMessage(0);
		}
		break;

		// Clean memory up
		// Started by WM_DESTROY
		case WM_NCDESTROY:
		{
			// Forced stop code
			return 0;
		}

		default:
		{
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}
}

const auto& my_windows_class = L"MY_CLASS";

int main(const int& argc, char** argv)
{
	gl::Initialize(gl::DisplayModes::DEPTH, gl::default_position, gl::default_resoulution);

	auto hinstance = gl::device::GetProcessInstance();

	auto property = gl::window::CreateProperty(hinstance, WndProc, my_windows_class);
	property.Register();

	auto window = gl::window::CreateWindow(property, L"MY_TITLE", -1, -1, 400, 300);

	window.Awake();
	window.Start();

	util::CancellationSource cancellation_source{};
	window.UpdateLoop(cancellation_source.get_token());

	return 0;
}
