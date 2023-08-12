module;
#include "MagicEnum.hpp"

export module Glib:Shader;
import <cstdint>;
import <string>;
import <string_view>;
import <filesystem>;
import <format>;
import :Object;

namespace gl
{
	namespace shader
	{
		export MAGIC_ENUM(
			ErrorCode, std::uint32_t
			, 7
			, None, Success, EmptyFilePath, InvalidFilePath, FileDoesNotExists, EmptyFile, NotValidShader, CompileFailed
		);

		inline constexpr std::uint32_t type_values[] =
		{
			0, 0x8B31, 0x8B30, 0x8B30, 0x8DD9, 0x8E88, 0x8E87
		};

		export MAGIC_ENUM_FROM(
			ShaderType, std::uint32_t
			, 6, type_values
			, None, Vertex, Fragment, Pixel, Geometry, Tessellation, TessellEvaluation
		);
	}

	export class [[nodiscard]] Shader : public gl::Object
	{
	private:
		using base = gl::Object;

	public:
		Shader(shader::ShaderType sh_type) noexcept;
		~Shader() noexcept;

		shader::ErrorCode LoadFrom(const std::filesystem::path& filepath) noexcept;
		shader::ErrorCode Compile(std::string_view content) noexcept;

		void Use(const unsigned int& program) noexcept;
		void Destroy() noexcept;

		[[nodiscard]] shader::ShaderType GetType() const noexcept;
		[[nodiscard]] bool IsLoaded() const noexcept;
		[[nodiscard]] bool IsUnloaded() const noexcept;
		[[nodiscard]] bool IsCompiled() const noexcept;

		bool operator==(const Shader& other) const noexcept = default;

		[[nodiscard]] static std::string_view GetLastError() noexcept;

		friend class Pipeline;

	private:
		shader::ShaderType myType = shader::ShaderType::None;
		bool isCompiled = false;
	};
}

export template<>
struct std::formatter<gl::shader::ShaderType>
{
	template<class FormatContext>
	auto format(const gl::shader::ShaderType& shtype, FormatContext& ctx) const
	{
		std::formatter<std::string> formatter;

		switch (shtype)
		{
			case gl::shader::ShaderType::None:
			{
				return formatter.format("", ctx);
			}
		}
	}

	constexpr auto parse(std::format_parse_context& ctx) noexcept
	{
		//return std::format_to(ctx.begin(), "{}", "asdsd");
	}
};
