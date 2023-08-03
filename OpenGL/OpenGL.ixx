module;
export module Glib;
export import :Utility;
export import :Pixel;
export import :TransformState;
export import :Transform;
export import :Comparator;
export import :State;
export import :Primitive;
export import :Object;
export import :BufferObject;
export import :BufferLayout;
export import :System;
import Glib.Windows.Definitions;

export namespace gl
{
	void Initialize(win32::ManagedWindow& client);
}
