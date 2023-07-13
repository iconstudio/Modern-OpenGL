export module Glib.Windows.Resource.Palette;
import <type_traits>;
import Glib.Windows.Definitions;
import Glib.Windows.IHandle;

export namespace gl::win32::resource
{
	class [[nodiscard]] Palette : public IHandle<native::RawPalette>
	{
	public:
	};
}
