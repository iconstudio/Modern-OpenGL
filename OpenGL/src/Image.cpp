module;
#include <Windows.h>
#include <atlimage.h>
#undef LoadImage

module Glib.Image;
import <cstdint>;
import <cstdio>;
import <stdexcept>;

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
	if (nullptr == buffer)
	{
		std::printf("Failed to load image: %s\n", path);
		throw std::runtime_error{ "Cannot acquire image buffer" };
	}

	bytesPerPixel = image.GetBPP();
	if (32 != bytesPerPixel)
	{
		std::printf("Cannot use the image: %s\n", path);
		throw std::runtime_error{ "Unsupported image format" };
	}

	imgHSize = image.GetWidth();
	imgVSize = image.GetHeight();
	imgBufferSize = imgHSize * imgVSize;

	const size_t stride = image.GetPitch();
	const std::uint8_t* const& pt_buffer = static_cast<const std::uint8_t*>(buffer);

	imgBuffer = std::make_unique<gl::BitmapPixel[]>(imgBufferSize);
	for (size_t i = 0; i < imgVSize; i++)
	{
		size_t voffset = i * stride;

		for (size_t j = 0; j < imgHSize; j++)
		{
			size_t hoffset = j * bytesPerPixel / 8; // must be 4 (32bit color)
			size_t offset = voffset + hoffset;

			std::uint8_t alpha = pt_buffer[offset + 3];
			std::uint8_t red = pt_buffer[offset + 2];
			std::uint8_t green = pt_buffer[offset + 1];
			std::uint8_t blue = pt_buffer[offset + 0];

			imgBuffer[i * imgHSize + j] = gl::BitmapPixel{ Colour{ red, green, blue, alpha } };
		}
	}

	std::printf("Loaded image: %s\n", path);

	image.Destroy();
}

