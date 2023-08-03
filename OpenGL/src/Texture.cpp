module;
#include <Windows.h>
#include <gl/GL.h>
#undef LoadImage

module Glib.Texture;
import <stdexcept>;

gl::Texture::Texture(gl::Image&& image)
	: base()
{
	myBlob = std::make_shared<Blob>(Blob
	{
		.imgBuffer = std::move(image.GetBuffer()),
		.width = image.GetWidth(),
		.height = image.GetHeight(),
	});
}

gl::Texture
gl::Texture::EmptyTexture(std::uint32_t w, std::uint32_t h)
noexcept
{
	return Texture();
}

gl::Texture::Texture(const gl::FilePath& path)
	: base()
{}

gl::Texture::Texture(const gl::FilePath& path
	, texture::Type type
	, texture::WrapMode hwrap, texture::WrapMode vwrap
	, texture::FilterMode min, texture::FilterMode mag)
	: base()
{
	Image img = gl::LoadImage(path);
	if (img.IsEmpty())
	{
		throw std::runtime_error("Failed to load image");
	}

	myBlob = std::make_shared<Blob>(Blob
	{
		.imgBuffer = std::move(img.GetBuffer()),
		.width = img.GetWidth(),
		.height = img.GetHeight(),
		.texType = type,
		.hWrap = hwrap,
		.vWrap = vwrap,
		.minFilter = min,
		.magFilter = mag,
	});
}

gl::Texture
gl::CreateEmptyTexture(std::uint32_t w, std::uint32_t h)
noexcept
{
	return gl::Texture();
}

gl::Texture
gl::LoadTexture(const gl::FilePath& path)
{
	return gl::Texture();
}

bool
gl::TryLoadTexture(const gl::FilePath& path, gl::Texture& output)
noexcept
{
	if (path.empty())
	{
		return false;
	}

	if (not path.has_filename())
	{
		return false;
	}

	if (not path.has_extension())
	{
		return false;
	}

	return false;
}

const std::size_t&
gl::Texture::GetWidth()
const
noexcept
{
	if (myBlob)
	{
		return myBlob->width;
	}
	else
	{
		return 0;
	}
}

const std::size_t&
gl::Texture::GetHeight()
const
noexcept
{
	if (myBlob)
	{
		return myBlob->height;
	}
	else
	{
		return 0;
	}
}

bool
gl::Texture::IsEmpty()
const noexcept
{
	return myBlob == nullptr;
}
