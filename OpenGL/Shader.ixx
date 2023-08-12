export module Glib:Shader;
import <cstdint>;
import <string_view>;
import <filesystem>;
import :Object;

export namespace gl
{
	namespace shader
	{
		enum class [[nodiscard]] ErrorCode : std::int32_t
		{
			None = 0,
		};

		enum class [[nodiscard]] ShaderType : std::int32_t
		{
			None = 0,
			Vertex = 0x8B31, // GL_VERTEX_SHADER
			Fragment = 0x8B30, // GL_FRAGMENT_SHADER
			Pixel = Fragment, // GL_FRAGMENT_SHADER
			Geometry = 0x8DD9, // GL_GEOMETRY_SHADER
			Tessellation = 0x8E88, // GL_TESS_CONTROL_SHADER
			TessellEvaluation = 0x8E87, // GL_TESS_EVALUATION_SHADER
		};
	}

	class [[nodiscard]] Shader
	{
	private:
		using base = gl::Object;

	public:
		Shader(shader::ShaderType sh_type) noexcept;
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

		friend class Pipeline;

	private:
		shader::ShaderType myType = shader::ShaderType::None;
	};
}
