module;
module Glib;

std::shared_ptr<gl::Framework>
gl::CreateFramework()
noexcept
{
	return std::make_shared<Framework>();
}
