module;
#include <Windows.h>
#include <gl/GL.h>

module Glib.Texture;
import <stdexcept>;

gl::Texture::Texture(nullptr_t)
noexcept
	: base()
{}

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

std::uint32_t
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

std::uint32_t
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
