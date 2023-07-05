module;
#include "Internal.hpp"

module Glib.Window;
import Glib.Device.ProcessInstance;
import Glib.Device.Event.API;

gl::window::Window::Window(nullptr_t)
noexcept
	: myInstance()
	, myClassName(nullptr)
	, myProcedure(nullptr)
	, base(nullptr)
{}

gl::window::Window::Window(const gl::window::WindowProperty& properties
	, const std::wstring_view& title
	, const gl::window::WindowStyle& style
	, const gl::window::WindowOption& option
	, const int& x, const int& y
	, const int& width, const int& height
) noexcept
	: myInstance(properties.GetInstance())
	, myClassName(properties.GetClass())
	, myProcedure(properties.GetProcedure())
	, base
	{
		gl::device::MakeNativeWindow(properties.GetInstance().myHandle,
		properties.GetClass(),
		title,
		Export(style), Export(option),
		x, y, width, height)
	}
{}

gl::window::Window::Window(gl::window::WindowProperty&& properties
	, const std::wstring_view& title
	, const gl::window::WindowStyle& style
	, const gl::window::WindowOption& option
	, const int& x, const int& y
	, const int& width, const int& height
) noexcept
	: myInstance(std::move(properties).GetInstance())
	, myClassName(std::move(properties).GetClass())
	, myProcedure(std::move(properties).GetProcedure())
	, base
	{
		gl::device::MakeNativeWindow(myInstance.myHandle
		, myClassName
		, title
		, Export(style), Export(option)
		, x, y, width, height)
	}
{}

gl::window::Window::Window(Window&& other)
noexcept
	: myInstance(std::exchange(other.myInstance, nullptr))
	, myProcedure(std::exchange(other.myProcedure, nullptr))
	, myClassName(std::exchange(other.myClassName, nullptr))
	, base(std::exchange(other.myHandle, nullptr))
{}

gl::window::Window&
gl::window::Window::operator=(Window&& other)
noexcept
{
	other.Swap(*this);
	return *this;
}

bool
gl::window::Window::Destroy()
noexcept
{
	return myHandle.Destroy();
}

void
gl::window::Window::Swap(Window& other)
noexcept
{
	std::swap(myHandle, other.myHandle);
	std::swap(myInstance, other.myInstance);
	std::swap(myClassName, other.myClassName);
	std::swap(myProcedure, other.myProcedure);
}

gl::window::Window::~Window()
noexcept
{
	if (nullptr != myClassName)
	{
		::UnregisterClass(myClassName, myInstance.myHandle);
	}

	Destroy();
}

void
gl::window::Window::Awake()
noexcept
{
	Show();
}

void
gl::window::Window::Start()
noexcept
{
	myHandle.StartUpdate();
}

void
gl::window::Window::UpdateLoop()
noexcept
{
	while (UpdateOnce())
	{}
}

bool
gl::window::Window::UpdateOnce()
noexcept
{
	gl::device::RawEvent event = gl::device::EventAPI::MakeEvent();

	if (gl::device::EventAPI::Pop(myHandle, event))
	{
		if (!gl::device::EventAPI::Translate(event))
		{
		}

		gl::device::EventAPI::Dispatch(event);
		return true;
	}

	return false;
}

bool
gl::window::Window::SendCommand(const gl::device::EventID& msg, const unsigned long long& lhs, const unsigned long& rhs)
const noexcept
{
	return myHandle.SendCommand(msg, lhs, rhs);
}

bool
gl::window::Window::SendCommand(const gl::device::EventID& msg)
const noexcept
{
	return SendCommand(msg, 0, 0);
}

bool
gl::window::Window::SendCommand(const device::Event& cmd)
const noexcept
{
	return myHandle.SendCommand(cmd);
}

bool
gl::window::Window::SendCommand(device::Event&& cmd)
const noexcept
{
	return myHandle.SendCommand(std::move(cmd));
}

bool
gl::window::Window::SendCommand(const device::EventID& id, const int& keycode, const long long& flags)
const noexcept
{
	return myHandle.SendCommand(id, keycode, flags);
}

bool
gl::window::Window::SendCommand(const device::EventID& id, const device::io::KeyCode& keycode, const device::io::KeyboardFlag& flags)
const noexcept
{
	return myHandle.SendCommand(id, keycode, flags);
}

bool
gl::window::Window::Show()
noexcept
{
	return myHandle.Show();
}

bool
gl::window::Window::Hide()
noexcept
{
	return myHandle.Hide();
}

bool
gl::window::Window::Maximize()
noexcept
{
	return myHandle.Maximize();
}

bool
gl::window::Window::Minimize()
noexcept
{
	return myHandle.Minimize();
}

bool
gl::window::Window::Restore()
noexcept
{
	return myHandle.Restore();
}

bool
gl::window::Window::Close()
noexcept
{
	return myHandle.Close();
}

bool
gl::window::Window::Redraw(const bool& flag)
noexcept
{
	return myHandle.Redraw(flag);
}

bool
gl::window::Window::EnableInput()
noexcept
{
	return myHandle.EnableInput();
}

bool
gl::window::Window::DisableInput()
noexcept
{
	return myHandle.DisableInput();
}

bool
gl::window::Window::IsMinimized()
const noexcept
{
	return myHandle.IsMinimized();
}

bool
gl::window::Window::IsMaximized()
const noexcept
{
	return myHandle.IsMaximized();
}

bool
gl::window::Window::IsRestored()
const noexcept
{
	return myHandle.IsRestored();
}

bool
gl::window::Window::IsInputEnabled()
const noexcept
{
	return myHandle.IsInputEnabled();
}

int
gl::window::Window::GetID()
const noexcept
{
	return 0;
}

gl::window::WindowStyle
gl::window::Window::GetStyle()
const noexcept
{
	return WindowStyle{ myHandle.GetStyle() };
}

gl::window::WindowOption
gl::window::Window::GetOption()
const noexcept
{
	return WindowOption{ myHandle.GetExStyle() };
}

long long
gl::window::Window::SetInternalValue(int index, const long long& value)
const noexcept
{
	return myHandle.SetInternalValue(index, value);
}

long long
gl::window::Window::SetInternalValue(int index, long long&& value)
const noexcept
{
	return myHandle.SetInternalValue(index, std::move(value));
}

long long
gl::window::Window::SetInternalUserData(const long long& value)
const noexcept
{
	return myHandle.SetInternalUserData(value);
}

long long
gl::window::Window::SetInternalUserData(long long&& value)
const noexcept
{
	return myHandle.SetInternalUserData(std::move(value));
}

long long
gl::window::Window::GetInternalValue(int index)
const noexcept
{
	return myHandle.GetInternalValue(index);
}

long long
gl::window::Window::GetInternalUserData()
const noexcept
{
	return myHandle.GetInternalUserData();
}

gl::Rect
gl::window::Window::GetDimensions()
const noexcept
{
	auto result = myHandle.GetDimensions();
	return gl::Rect
	{
		result.left,
			result.top,
			result.right - result.left,
			result.bottom - result.top
	};
}

bool
gl::window::Window::TryGetDimensions(gl::Rect& output)
const noexcept
{
	auto result = gl::device::MakeNativeRect();
	const bool ok = myHandle.TryGetDimensions(result);
	if (ok)
	{
		output = gl::Rect
		{
			result.left, result.top, result.right - result.left, result.bottom - result.top
		};
	}

	return ok;
}
