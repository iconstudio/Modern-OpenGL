export module Glib.Device.Resource.Palette;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;

export namespace gl::win32::resource
{
	class [[nodiscard]] Palette : public IHandle<native::RawPalette>
	{
	public:
	};
}
