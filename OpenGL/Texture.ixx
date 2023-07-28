export module Glib.Texture;
import <string_view>;
import <filesystem>;
import Glib;

export namespace gl
{
	using FilePath = std::filesystem::path;

	class [[nodiscard]] Texture : public gl::BufferObject
	{
	public:
		Texture() noexcept;
		Texture(nullptr_t) noexcept;
		~Texture() noexcept;




		Texture(const Texture& other) noexcept;
		Texture(Texture&& other) noexcept;
		Texture& operator=(const Texture& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		friend Texture LoadTexture(const FilePath& path);
		friend bool TryLoadTexture(const FilePath& path, Texture& output) noexcept;

	private:
		Texture(const FilePath& path);
	};
}
