module;
#include <Windows.h>
export module Glib.Windows;

export namespace gl::device
{
	struct [[nodiscard]] Context
	{
		HDC hdc;
		HGLRC hglrc;
	};
}
