module;
#include <Windows.h>
#include <gl/GL.h>
#undef LoadImage

module Glib.Texture;
import <stdexcept>;

gl::Texture::Texture(gl::Image&& image)
	: base()
{
	myBlob = std::make_shared<texture::Blob>();

	myBlob->imgBuffer = std::move(image.GetBuffer());
	myBlob->width = image.GetWidth();
	myBlob->height = image.GetHeight();
}

void
gl::Texture::Bind()
const noexcept
{
	if (myBlob)
	{
		glBindTexture(GL_TEXTURE_2D, myID);
	}
}

void
gl::Texture::Unbind()
const noexcept
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


gl::Texture
gl::Texture::Copy()
const
{
	return gl::Texture(*this);
}

bool
gl::Texture::TryCopy(Texture& output)
const noexcept
{
	return false;
}

void
gl::Texture::Destroy()
noexcept
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
	Image img = gl::LoadImage(path);
	if (img.IsEmpty())
	{
		throw std::runtime_error("Failed to load image");
	}

	myBlob = std::make_shared<texture::Blob>();
	myBlob->imgBuffer = std::move(img.GetBuffer());
	myBlob->width = img.GetWidth();
	myBlob->height = img.GetHeight();
	myBlob->texType = type;
	myBlob->hWrap = hwrap;
	myBlob->vWrap = vwrap;
	myBlob->minFilter = min;
	myBlob->magFilter = mag;
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
