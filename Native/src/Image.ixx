export module Glibe.Device.Resource.Image;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;
import Glib.Device.Colour;

export namespace gl::device::resource
{
	class [[nodiscard]] Image : public IHandle<native::RawImage>
	{
	public:
		Image() noexcept;



	private:
		long cachedWidth = 0, cachedHeight = 0;
	};
}
