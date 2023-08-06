module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>
#include <GL/GLu.h>

module Glib;
import <stdexcept>;
import <cstdio>;
import Utility.Print;
import Glib.Windows.Context;
import Glib.Windows.Client;
import Glib.Windows.ManagedClient;

namespace gl
{
	void Initialize(win32::ManagedWindow& client)
	{
		win32::DeviceContext ctx = client.AcquireContext();
	}
}
