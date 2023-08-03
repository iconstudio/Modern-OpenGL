module;
#include <Windows.h>
#include <atlimage.h>
#undef LoadImage

module Glib.Image;
import <cstdint>;
import <cstdio>;
import <stdexcept>;

gl::Image
gl::LoadImage(const gl::FilePath& filepath)
{
	return gl::Image{ filepath };
}

gl::Image::Image(const gl::FilePath& filepath)
{
	ATL::CImage image{};

	HRESULT check = image.Load(filepath.c_str());
	if (FAILED(check))
	{
		std::wprintf(L"Failed to load image: %s\n", filepath.c_str());
		throw std::runtime_error{ "Failed to load image" };
	}

	if (HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) == check)
	{
		std::wprintf(L"Failed to load image: %s\n", filepath.c_str());
		throw std::runtime_error{ "Failed to load image" };
	}

	const void* buffer = image.GetBits();
	if (nullptr == buffer)
	{
		std::wprintf(L"Failed to load image: %s\n", filepath.c_str());
		throw std::runtime_error{ "Cannot acquire image buffer" };
	}

	bytesPerPixel = image.GetBPP();
	if (32 != bytesPerPixel)
	{
		std::wprintf(L"Cannot use the image: %s\n", filepath.c_str());
		throw std::runtime_error{ "Unsupported image format" };
	}

	imgHSize = image.GetWidth();
	imgVSize = image.GetHeight();
	imgBufferSize = imgHSize * imgVSize * 4;

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

gl::Image::buffer_t&
gl::Image::GetBuffer()
& noexcept
{
	return imgBuffer;
}

const gl::Image::buffer_t&
gl::Image::GetBuffer()
const& noexcept
{
	return imgBuffer;
}

gl::Image::buffer_t&&
gl::Image::GetBuffer()
&& noexcept
{
	return std::move(imgBuffer);
}

const gl::Image::buffer_t&&
gl::Image::GetBuffer()
const&& noexcept
{
	return std::move(imgBuffer);
}

std::size_t
gl::Image::GetBufferSize()
const noexcept
{
	return imgBufferSize;
}

std::size_t
gl::Image::GetWidth()
const noexcept
{
	return imgHSize;
}

size_t
gl::Image::GetHeight()
const noexcept
{
	return imgVSize;
}

size_t
gl::Image::GetBytesPerPixel()
const noexcept
{
	return bytesPerPixel;
}

bool
gl::Image::IsEmpty()
const noexcept
{
	return nullptr == imgBuffer;
}
