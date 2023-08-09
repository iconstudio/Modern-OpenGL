export module Glib.Image;
import <memory>;
import <filesystem>;
import Glib;

export namespace gl
{
	using FilePath = std::filesystem::path;

	class [[nodiscard]] Image
	{
	public:
		using buffer_t = std::unique_ptr<gl::BitmapPixel[]>;

		~Image() noexcept = default;

		[[nodiscard]] buffer_t& GetBuffer() noexcept;
		[[nodiscard]] const buffer_t& GetBuffer() const noexcept;
		[[nodiscard]] size_t GetBufferSize() const noexcept;
		[[nodiscard]] size_t GetWidth() const noexcept;
		[[nodiscard]] size_t GetHeight() const noexcept;
		[[nodiscard]] size_t GetBytesPerPixel() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		[[nodiscard]] friend Image LoadImage(const FilePath& filepath);

		Image(const Image&) = delete;
		Image(Image&&) noexcept = default;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) noexcept = default;

	private:
		Image() noexcept = default;
		Image(const FilePath& filepath);

		buffer_t imgBuffer;
		size_t imgBufferSize;
		size_t imgHSize, imgVSize;
		size_t bitsPerPixel;
	};

	[[nodiscard]] Image LoadImage(const FilePath& filepath);
}
