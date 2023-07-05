#include "Internal.hpp"
import Glib.Definitions;
import Utility.Monad.Loosen;

using gl::device::FilePath;

inline constexpr unsigned int DefaultFlag = LR_LOADFROMFILE | LR_DEFAULTSIZE;

util::LooseMonad<HBITMAP, unsigned int>
_LoadBitmap(const FilePath& path)
noexcept
{
	HANDLE handle = LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, DefaultFlag);
	if (nullptr == handle)
	{
		return ::GetLastError();
	}

	return static_cast<HBITMAP>(handle);
}
