module;
#include <Windows.h>
#include <atlimage.h>
#undef LoadImage

module Glib.Image;
import <cstdint>;
import <cstdio>;
import <stdexcept>;
import <memory>;

gl::Image::Image(nullptr_t)
noexcept
	: Image()
{}

gl::Image
LoadImage(const gl::FilePath& filepath)
{
	return gl::Image{ filepath };
}

gl::Image::Image(const gl::FilePath& filepath)
{
	ATL::CImage image{};

	const char* const& path = filepath.string().c_str();

	HRESULT check = image.Load(path);
	if (FAILED(check))
	{
		std::printf("Failed to load image: %s\n", path);
		throw std::runtime_error{ "Failed to load image" };
	}

	if (HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) == check)
	{
		std::printf("Failed to load image: %s\n", path);
		throw std::runtime_error{ "Failed to load image" };
	}

	const void* buffer = image.GetBits();
	if (buffer == nullptr)
	{
		std::printf("Failed to load image: %s\n", path);
		throw std::runtime_error{ "Cannot acquire image buffer" };
	}

	imgHSize = image.GetWidth();
	imgVSize = image.GetHeight();
	bytesPerPixel = image.GetBPP();
	imgBufferSize = imgHSize * imgVSize * bytesPerPixel / 8;

	imgBuffer = new std::uint8_t[imgBufferSize];

	std::memcpy(imgBuffer, buffer, imgBufferSize);

	std::printf("Loaded image: %s\n", path);

	image.Destroy();
}

