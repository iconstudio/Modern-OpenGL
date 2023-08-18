module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>

module Glib;
import <cstdint>;
import <cstdio>;
import <type_traits>;
import Utility.IO.File;
import :Shader;

constinit static GLchar lastError[512]{};

inline constexpr std::string_view noError = "No Error";

gl::Shader::Shader(shader::ShaderType sh_type)
noexcept
	: base(NULL)
	, myType(sh_type)
{}

gl::Shader::~Shader()
noexcept
{
	Destroy();
}

gl::shader::ErrorCode
gl::Shader::LoadFrom(const std::filesystem::path& filepath)
noexcept
{
	if (filepath.empty())
	{
		return shader::ErrorCode::EmptyFilePath;
	}

	if (!filepath.has_filename())
	{
		return shader::ErrorCode::InvalidFilePath;
	}

	util::io::File shfile{ filepath, util::io::file::OpenModes::Binary };

	if (!shfile.IsOpen())
	{
		return shader::ErrorCode::FileDoesNotExists;
	}

	std::string contents = shfile.Contents();
	if (!contents.empty())
	{
		return shader::ErrorCode::EmptyFile;
	}

	return Compile(std::move(contents));
}

bool FindMainOnShader(std::string_view source) noexcept;
bool CompileShader(std::uint32_t id, const char* const source) noexcept;

gl::shader::ErrorCode
gl::Shader::Compile(std::string_view source)
noexcept
{
	if (not FindMainOnShader(source))
	{
		return shader::ErrorCode::NotValidShader;
	}

	const std::uint32_t shid = ::glCreateShader(static_cast<GLenum>(myType));

	if (not CompileShader(shid, source.data()))
	{
		return shader::ErrorCode::CompileFailed;
	}

	SetID(shid);

	return shader::ErrorCode::Success;
}

bool
FindMainOnShader(std::string_view source)
noexcept
{
	constexpr std::string_view ext_main{ "main" };
	const size_t off = source.find(ext_main, 0);
	if (std::string::npos == off)
	{
		return false;
	}

	return true;
}

bool
CompileShader(std::uint32_t id, const char* const source)
noexcept
{
	::glShaderSource(id, 1, std::addressof(source), nullptr);

	::glCompileShader(id);

	int success{};
	if (::glGetShaderiv(id, GL_COMPILE_STATUS, &success); 0 == success)
	{
		::glGetShaderInfoLog(id, sizeof(lastError), NULL, lastError);
		return false;
	}

	return true;
}

void
gl::Shader::Destroy()
noexcept
{
	if (IsLoaded())
	{
		::glDeleteShader(GetID());
		SetID(NULL);
	}
}

gl::shader::ShaderType
gl::Shader::GetType()
const noexcept
{
	return myType;
}

bool
gl::Shader::IsLoaded()
const noexcept
{
	return myType != gl::shader::ShaderType::None && NULL != GetID();
}

bool
gl::Shader::IsUnloaded()
const noexcept
{
	return myType == gl::shader::ShaderType::None || NULL == GetID();
}

std::string_view
gl::Shader::GetLastError()
noexcept
{
	if (nullptr == ::lastError)
	{
		return ::noError;
	}

	return std::string_view{ ::lastError };
}
