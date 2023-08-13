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

		bool operator==(const Shader& other) const noexcept = default;

		[[nodiscard]] static std::string_view GetLastError() noexcept;

		friend class Pipeline;

	private:
		shader::ShaderType myType = shader::ShaderType::None;
	};
}

export template<>
struct std::formatter<gl::shader::ShaderType>
{
	template<class FormatContext>
	auto format(const gl::shader::ShaderType& shtype, FormatContext& ctx) const noexcept
	{
		constexpr auto& vallist = gl::shader::MAGIC_ENUMLIST(ShaderType);
		constexpr auto& namelist = gl::shader::MAGIC_ENUMFULL(ShaderType);
		constexpr auto& valsize = gl::shader::MAGIC_ENUMSIZE(ShaderType);

		const auto& beg = vallist;
		const auto& end = vallist + valsize;
		const auto& it = std::find(beg, end, shtype);
		if (end != it)
		{
			ptrdiff_t index = it - beg;
			return std::format_to(ctx.out(), "{}", namelist[index]);
		}

		return std::format_to(ctx.out(), "{}", "None Type");
	}

	template<class FormatContext>
	constexpr auto parse(FormatContext& ctx) const noexcept
	{
		return ctx.begin();
	}
};

export template<>
struct std::formatter<gl::shader::ErrorCode>
{
	template<class FormatContext>
	auto format(const gl::shader::ErrorCode& shtype, FormatContext& ctx) const noexcept
	{
		constexpr auto& vallist = gl::shader::MAGIC_ENUMLIST(ErrorCode);
		constexpr auto& namelist = gl::shader::MAGIC_ENUMFULL(ErrorCode);
		constexpr auto& valsize = gl::shader::MAGIC_ENUMSIZE(ErrorCode);

		const auto& beg = vallist;
		const auto& end = vallist + valsize;
		const auto& it = std::find(beg, end, shtype);
		if (end != it)
		{
			ptrdiff_t index = it - beg;
			return std::format_to(ctx.out(), "{}", namelist[index]);
		}

		return std::format_to(ctx.out(), "{}", "Nothing");
	}

	template<class FormatContext>
	constexpr auto parse(FormatContext& ctx) const noexcept
	{
		return ctx.begin();
	}
};
