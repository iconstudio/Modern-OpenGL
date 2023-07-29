module;
#include <Windows.h>
#include <gl/GL.h>
module Glib.Texture;

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

gl::Texture
gl::CreateEmptyTexture(std::uint32_t w, std::uint32_t h)
noexcept
{
	return Texture();
}

gl::Texture
gl::LoadTexture(const gl::FilePath& path)
{
	return Texture();
}

bool
gl::TryLoadTexture(const gl::FilePath& path, gl::Texture& output)
noexcept
{
	return false;
}
