export module Glib;
import <memory>;
import Glib.Framework;

export namespace gl
{
	std::shared_ptr<Framework> CreateFramework() noexcept;
}
