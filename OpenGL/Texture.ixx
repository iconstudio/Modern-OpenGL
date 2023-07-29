export module Glib.Texture;
import <cstdint>;
import <string_view>;
import <filesystem>;
import <memory>;
import Utility.Atom;
import Utility.Atomic;
import Glib;

export namespace gl
{
	using FilePath = std::filesystem::path;

	class [[nodiscard]] Texture : public gl::BufferObject
	{
	private:
		struct [[nodiscard]] TextureBlob
		{
			std::uint32_t width, height;
			std::uint8_t* data = nullptr;
			util::atomic_size_t refCount = 1;
		};

	public:
		Texture() noexcept;
		Texture(nullptr_t) noexcept;
		~Texture() noexcept;

		void Bind() const noexcept;
		void Use() const noexcept;
		void Destroy() noexcept;

		[[nodiscard]] std::uint32_t GetWidth() const noexcept;
		[[nodiscard]] std::uint32_t GetHeight() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		Texture(const Texture& other) noexcept;
		Texture(Texture&& other) noexcept;
		Texture& operator=(const Texture& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		[[nodiscard]] static Texture EmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
		[[nodiscard]] friend Texture CreateEmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
		[[nodiscard]] friend Texture LoadTexture(const FilePath& path);
		friend bool TryLoadTexture(const FilePath& path, Texture& output) noexcept;

	private:
		Texture(const FilePath& path);

		std::unique_ptr<TextureBlob> myBlob = nullptr;
		util::Atom<const std::uint32_t> hSize = 32U, vSize = 32U;
	};
}
