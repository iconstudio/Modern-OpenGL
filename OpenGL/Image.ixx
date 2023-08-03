export module Glib.Image;
import <filesystem>;
import <mutex>;
import Glib;
export import Utility.IO.File;

export namespace gl
{
	using util::io::FilePath;

	class [[nodiscard]] Image
	{
	public:
		Image() noexcept = default;
		~Image() noexcept = default;

		Image(nullptr_t) noexcept;

		[[nodiscard]] friend Image LoadImage(const FilePath& filepath);

		Image(const Image&) = delete;
		Image(Image&&) noexcept = default;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) noexcept = default;

	private:
		Image(const FilePath& filepath);
	};

	[[nodiscard]] Image LoadImage(const FilePath& filepath);
}
