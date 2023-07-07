export module Glibe.Device.Resource.Image;
import <type_traits>;
import Glib.Definitions;

export namespace gl::device::resource
{
	class [[nodiscard]] Image
	{
	public:
		Image() noexcept;

	private:
		native::RawImage myHandle;
	};
}
