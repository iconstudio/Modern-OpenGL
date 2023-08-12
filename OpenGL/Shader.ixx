export module Glib:Shader;
import <cstdint>;
import <string_view>;
import <filesystem>;

export namespace gl
{
	namespace shader
	{
		enum class [[nodiscard]] ErrorCode : std::int32_t
		{
			None = 0,
		};
	}

	class [[nodiscard]] Shader
	{
	public:
		Shader() noexcept;
		~Shader() noexcept;

		bool Load(std::string_view content) noexcept;
		bool LoadFrom(const std::filesystem::path& filepath) noexcept;
		bool Compile() noexcept;
		bool TryCompile(shader::ErrorCode& error_code) noexcept;

		void Use(const unsigned int& program) noexcept;

		[[nodiscard]] bool IsLoaded() const noexcept;
		[[nodiscard]] bool IsUnloaded() const noexcept;
		[[nodiscard]] bool IsCompiled() const noexcept;

		bool operator==(const Shader& other) const noexcept = default;
	};
}
