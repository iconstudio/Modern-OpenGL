#include "Internal.hpp"
import Glib.Definitions;
import Utility.Monad.Loosen;

using gl::device::FilePath;

inline constexpr unsigned int _DefaultFlag = LR_LOADFROMFILE | LR_DEFAULTSIZE;

util::LooseMonad<HBITMAP, unsigned int>
_LoadBitmap(const FilePath& path)
noexcept
{
	HANDLE handle = ::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, _DefaultFlag);
	if (nullptr == handle)
	{
		return ::GetLastError();
	}
	else
	{
		return static_cast<HBITMAP>(handle);
	}
}

util::LooseMonad<HICON, unsigned int>
_LoadIcon(const FilePath& path)
noexcept
{
	HANDLE handle = ::LoadImage(nullptr, path.c_str(), IMAGE_ICON, 0, 0, _DefaultFlag);
	if (nullptr == handle)
	{
		return ::GetLastError();
	}
	else
	{
		return static_cast<HICON>(handle);
	}
}

util::LooseMonad<HCURSOR, unsigned int>
_LoadCursor(const FilePath& path)
noexcept
{
	HANDLE handle = ::LoadImage(nullptr, path.c_str(), IMAGE_CURSOR, 0, 0, _DefaultFlag);
	if (nullptr == handle)
	{
		return ::GetLastError();
	}
	else
	{
		return static_cast<HCURSOR>(handle);
	}
}
