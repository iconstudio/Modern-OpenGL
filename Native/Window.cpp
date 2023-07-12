module;
#include "Internal.hpp"

module Glib.Window;
import Glib.Device.ProcessInstance;
import Glib.Device.Event.API;

gl::win32::Window::Window(nullptr_t)
noexcept
	: myInstance()
	, myClassName(nullptr)
	, myProcedure(nullptr)
	, base(nullptr)
{}

gl::win32::Window::Window(const gl::win32::WindowProperty& properties
	, const std::wstring_view& title
	, const gl::win32::WindowStyle& style
	, const gl::win32::WindowOption& option
	, const int& x, const int& y
	, const int& width, const int& height
) noexcept
	: myInstance(properties.GetInstance())
	, myClassName(properties.GetClass())
	, myProcedure(properties.GetProcedure())
	, base
	{
		gl::win32::MakeNativeWindow(properties.GetInstance().myHandle,
		properties.GetClass(),
		title,
		Export(style), Export(option),
		x, y, width, height)
	}
{}

gl::win32::Window::Window(gl::win32::WindowProperty&& properties
	, const std::wstring_view& title
	, const gl::win32::WindowStyle& style
	, const gl::win32::WindowOption& option
	, const int& x, const int& y
	, const int& width, const int& height
) noexcept
	: myInstance(std::move(properties).GetInstance())
	, myClassName(std::move(properties).GetClass())
	, myProcedure(std::move(properties).GetProcedure())
	, base
	{
		gl::win32::MakeNativeWindow(myInstance.myHandle
		, myClassName
		, title
		, Export(style), Export(option)
		, x, y, width, height)
	}
{}

gl::win32::Window::Window(Window&& other)
noexcept
	: myInstance(std::exchange(other.myInstance, nullptr))
	, myProcedure(std::exchange(other.myProcedure, nullptr))
	, myClassName(std::exchange(other.myClassName, nullptr))
	, base(std::exchange(other.myHandle, nullptr))
{}

gl::win32::Window&
gl::win32::Window::operator=(Window&& other)
noexcept
{
	other.Swap(*this);
	return *this;
}

void
gl::win32::Window::Swap(Window& other)
noexcept
{
	std::swap(myHandle, other.myHandle);
	std::swap(myInstance, other.myInstance);
	std::swap(myClassName, other.myClassName);
	std::swap(myProcedure, other.myProcedure);
}

gl::win32::Window::~Window()
noexcept
{
	if (nullptr != myClassName)
	{
		::UnregisterClass(myClassName, myInstance.myHandle);
	}

	Destroy();
}

void
gl::win32::Window::Awake()
noexcept
{
	base::StartUpdate();
	Show();
}

void
gl::win32::Window::Start()
noexcept
{
	while (UpdateOnce())
	{}
}

bool
gl::win32::Window::UpdateOnce()
noexcept
{
	gl::win32::RawEvent event = gl::win32::EventAPI::MakeEvent();

	if (gl::win32::EventAPI::Pop(myHandle, event))
	{
		if (!gl::win32::EventAPI::Translate(event))
		{
		}

		gl::win32::EventAPI::Dispatch(event);
		return true;
	}

	return false;
}

gl::win32::WindowStyle
gl::win32::Window::GetStyle()
const noexcept
{
	return WindowStyle{ base::GetStyle() };
}

gl::win32::WindowOption
gl::win32::Window::GetOption()
const noexcept
{
	return WindowOption{ base::GetExStyle() };
}
