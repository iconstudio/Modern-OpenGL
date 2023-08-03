export module Glib.Image;
import <string_view>;
import <filesystem>;
import <mutex>;
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
		Image(const FilePath& filepath);

		Image(const Image&) = delete;
		Image(Image&&) noexcept = default;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) noexcept = default;

	private:
		static std::once_flag initFlag;
	};
}
