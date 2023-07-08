module;
module Glib.Framework;

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
