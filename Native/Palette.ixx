export module Glib.Device.Resource.Palette;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;

export namespace gl::device::resource
{
	class [[nodiscard]] Palette : public IHandle<native::RawPalette>
	{
	public:
	};
}
