export module Glib.Texture:Image;
import <filesystem>;
import Glib;

export namespace gl
{
	using FilePath = std::filesystem::path;

	class [[nodiscard]] Image
	{
	public:
		Image() noexcept = default;
		~Image() noexcept = default;

		Image(nullptr_t) noexcept;
		Image(const FilePath& path);

		Image(const Image&) = delete;
		Image(Image&&) noexcept = default;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) noexcept = default;
	};
}
