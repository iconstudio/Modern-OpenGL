export module Glib.Texture;
import <cstdint>;
import <string_view>;
import <filesystem>;
import <memory>;
import Glib;

export namespace gl
{
	using FilePath = std::filesystem::path;

	namespace texture
	{
		enum class [[nodiscard]] WrapMode : std::uint32_t
		{
			Repeat = 0x2901,
			MirroredRepeat = 0x8370,
			ClampToEdge = 0x812F,
			ClampToBorder = 0x812D,
			MirrorClampToEdge = 0x8743
		};

		enum class [[nodiscard]] FilterMode : std::uint32_t
		{
			Nearest = 0x2600,
			Linear = 0x2601,
			NearestMipmapNearest = 0x2702,
			LinearMipmapNearest = 0x2703,
			NearestMipmapLinear = 0x2704,
			LinearMipmapLinear = 0x2705
		};

		enum class [[nodiscard]] Type : std::uint32_t
		{
			Tex1D = 0x0DE0,
			Tex2D = 0x0DE1,
			Tex3D = 0x806F,
			Tex1DArray = 0x8C18,
			Tex2DArray = 0x8C1A,
			TexCubeMap = 0x8513,
			TexCubeMapArray = 0x9009,
			Tex2DMultisample = 0x9100,
			Tex2DMultisampleArray = 0x9102
		};
	}

	class [[nodiscard]] Texture : public gl::BufferObject
	{
	private:
		struct [[nodiscard]] TextureBlob
		{
			std::uint32_t width, height;
			std::uint8_t* data = nullptr;
		};

	public:
		using base = gl::BufferObject;

		Texture() = default;
		~Texture() = default;

		Texture(nullptr_t) noexcept;

		void Bind() const noexcept;
		void Use() const noexcept;
		void Destroy() noexcept;

		[[nodiscard]] std::uint32_t GetWidth() const noexcept;
		[[nodiscard]] std::uint32_t GetHeight() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		Texture(Texture&&) noexcept = default;
		Texture& operator=(Texture&&) noexcept = default;

		[[nodiscard]] static Texture EmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
		[[nodiscard]] friend Texture CreateEmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
		[[nodiscard]] friend Texture LoadTexture(const FilePath& path);
		friend bool TryLoadTexture(const FilePath& path, Texture& output) noexcept;

	private:
		Texture(const FilePath& path);

		Texture(const Texture&) noexcept = default;
		Texture& operator=(const Texture&) noexcept = default;

		std::shared_ptr<TextureBlob> myBlob = nullptr;
		std::uint32_t hSize = 1U, vSize = 1U;

		texture::Type myType = texture::Type::Tex2D;
		texture::WrapMode hWrap = texture::WrapMode::Repeat, vWrap = texture::WrapMode::Repeat;
		texture::FilterMode minFilter = texture::FilterMode::Linear, magFilter = texture::FilterMode::Linear;
	};

	[[nodiscard]] Texture CreateEmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
	[[nodiscard]] Texture LoadTexture(const FilePath& path);
	bool TryLoadTexture(const FilePath& path, Texture& output) noexcept;
}
