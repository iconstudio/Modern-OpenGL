export module Glib.Texture;
import <cstdint>;
import <string_view>;
import <filesystem>;
import <memory>;
import Glib;
export import Glib.Image;

export namespace gl
{
	namespace texture
	{
		enum class [[nodiscard]] WrapMode : std::uint32_t
		{
			None = 0,
			Repeat = 0x2901,
			MirroredRepeat = 0x8370,
			ClampToEdge = 0x812F,
			ClampToBorder = 0x812D,
			MirrorClampToEdge = 0x8743
		};

		enum class [[nodiscard]] FilterMode : std::uint32_t
		{
			None = 0,
			Nearest = 0x2600,
			Linear = 0x2601,
			NearestMipmapNearest = 0x2702,
			LinearMipmapNearest = 0x2703,
			NearestMipmapLinear = 0x2704,
			LinearMipmapLinear = 0x2705
		};

		enum class [[nodiscard]] Type : std::uint32_t
		{
			None = 0,
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

		inline constexpr texture::Type DefaultTexType = texture::Type::Tex2D;
		inline constexpr texture::WrapMode DefaultTexHWrap = texture::WrapMode::Repeat;
		inline constexpr texture::WrapMode DefaultTexVWrap = texture::WrapMode::Repeat;
		inline constexpr texture::FilterMode DefaultTexMinFt = texture::FilterMode::Linear;
		inline constexpr texture::FilterMode DefaultTexMaxFt = texture::FilterMode::Linear;

		struct [[nodiscard]] Blob : public std::enable_shared_from_this<Blob>
		{
			constexpr void swap(Blob& other) noexcept
			{
				imgBuffer.swap(other.imgBuffer);
				std::swap(width, other.width);
				std::swap(height, other.height);
				std::swap(texType, other.texType);
				std::swap(hWrap, other.hWrap);
				std::swap(vWrap, other.vWrap);
				std::swap(minFilter, other.minFilter);
				std::swap(magFilter, other.magFilter);
			}

			std::unique_ptr<gl::BitmapPixel[]> imgBuffer = nullptr;
			std::size_t width = 1U, height = 1U;
			texture::Type texType = DefaultTexType;
			texture::WrapMode hWrap = DefaultTexHWrap;
			texture::WrapMode vWrap = DefaultTexVWrap;
			texture::FilterMode minFilter = DefaultTexMinFt;
			texture::FilterMode magFilter = DefaultTexMaxFt;
		};
	}

	class [[nodiscard]] Texture
		: public gl::Object
	{
	public:
		using base = gl::Object;

		Texture() = default;
		~Texture() = default;

		Texture(gl::Image&& image);

		void Bind() const noexcept;
		void Unbind() const noexcept;
		[[nodiscard]] Texture Copy() const;
		bool TryCopy(Texture& output) const;
		void Destroy() noexcept;

		[[nodiscard]] texture::Type GetType() const noexcept;
		[[nodiscard]] texture::WrapMode GetHorizontalWrapMode() const noexcept;
		[[nodiscard]] texture::WrapMode GetVerticalWrapMode() const noexcept;
		[[nodiscard]] texture::FilterMode GetMinFilter() const noexcept;
		[[nodiscard]] texture::FilterMode GetMagFilter() const noexcept;
		[[nodiscard]] std::size_t GetWidth() const noexcept;
		[[nodiscard]] std::size_t GetHeight() const noexcept;

		[[nodiscard]] bool IsEmpty() const noexcept;

		Texture(Texture&&) noexcept = default;
		Texture& operator=(Texture&&) noexcept = default;

		[[nodiscard]] static Texture EmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
		[[nodiscard]] friend Texture CreateEmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
		[[nodiscard]] friend Texture LoadTexture(const FilePath& path);
		friend bool TryLoadTexture(const FilePath& path, Texture& output) noexcept;

	private:
		Texture(const FilePath& path
			, texture::Type type = texture::DefaultTexType
			, texture::WrapMode hwrap = texture::DefaultTexHWrap
			, texture::WrapMode vwrap = texture::DefaultTexVWrap
			, texture::FilterMode min = texture::DefaultTexMinFt
			, texture::FilterMode mag = texture::DefaultTexMaxFt);

		Texture(const Texture&) = default;
		Texture& operator=(const Texture&) = default;

		std::shared_ptr<texture::Blob> myBlob = nullptr;
	};

	[[nodiscard]] Texture CreateEmptyTexture(std::uint32_t w, std::uint32_t h) noexcept;
	[[nodiscard]] Texture LoadTexture(const FilePath& path);
	bool TryLoadTexture(const FilePath& path, Texture& output) noexcept;
}
