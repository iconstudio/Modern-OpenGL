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
gl::Framework::Initialize(const gl::framework::Descriptor& setup)
{
	return {};
}

void
gl::Framework::Run()
noexcept
{}
