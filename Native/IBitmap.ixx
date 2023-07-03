module;
#include "Internal.hpp"

export module Glib.Device.Resource.IBitmap;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device::resource
{
	class [[nodiscard]] BitmapFactory
	{
	public:
	};

	class [[nodiscard]] Bitmap : public IHandle<native::RawBitmap>
	{
	public:
	};
}
