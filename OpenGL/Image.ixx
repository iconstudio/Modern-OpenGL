export module Glib.Image;
import <memory>;
import Glib;
export import Utility.IO.File;

export namespace gl
{
	using util::io::FilePath;

	class [[nodiscard]] Image
	{
	public:
		[[nodiscard]] friend Image LoadImage(const FilePath& filepath);

		[[nodiscard]] const gl::BitmapPixel* GetBuffer() const noexcept;
		[[nodiscard]] size_t GetBufferSize() const noexcept;
		[[nodiscard]] size_t GetWidth() const noexcept;
		[[nodiscard]] size_t GetHeight() const noexcept;
		[[nodiscard]] size_t GetBytesPerPixel() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		Image(const Image&) = delete;
		Image(Image&&) noexcept = default;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) noexcept = default;

	private:
		Image() noexcept = default;
		~Image() noexcept = default;

		Image(const FilePath& filepath);

		std::unique_ptr<gl::BitmapPixel[]> imgBuffer;
		size_t imgBufferSize;
		size_t imgHSize, imgVSize;
		size_t bytesPerPixel;
	};

	[[nodiscard]] Image LoadImage(const FilePath& filepath);
}
