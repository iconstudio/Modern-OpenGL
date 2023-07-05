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
	base::StartUpdate();
	Show();
}

void
gl::window::Window::Start()
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

gl::window::WindowStyle
gl::window::Window::GetStyle()
const noexcept
{
	return WindowStyle{ base::GetStyle() };
}

gl::window::WindowOption
gl::window::Window::GetOption()
const noexcept
{
	return WindowOption{ base::GetExStyle() };
}
