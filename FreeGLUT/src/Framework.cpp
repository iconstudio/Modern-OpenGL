module;
#include <Windows.h>

module Glib.Framework;
import Glib.Display;
import Glib.Window.Factory;

gl::Framework::Framework()
noexcept
	: base()
	, myInstance(nullptr)
{
}

gl::Framework::~Framework()
noexcept
{
}

gl::framework::InitError
gl::Framework::Initialize(const int& x, const int& y, const int& width, const int& height)
{
	return {};
}

void
gl::Framework::Run()
noexcept
{}
