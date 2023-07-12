export module Glibe.Device.Resource.Image;
import <type_traits>;
import Glib.Definitions;
import Glib.Device.IHandle;
import Glib.Device.Colour;

export namespace gl::win32::resource
{
	class [[nodiscard]] Image : public IHandle<native::RawBitmap>
	{
	public:
		using base = IHandle<native::RawBitmap>;

		constexpr Image() noexcept;



	private:
		long cachedWidth = 0, cachedHeight = 0;
		void* m_pBits;
		int m_nWidth;
		int m_nHeight;
		int m_nPitch;
		int m_nBPP;
		bool m_bIsDIBSection;
		bool m_bHasAlphaChannel;
		long m_iTransparentColor;
		unsigned long m_clrTransparentColor;
	};
}
