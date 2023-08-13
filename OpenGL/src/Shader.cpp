module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>

module Glib;
import <cstdio>;
import <type_traits>;
import <string>;
import <algorithm>;
import <functional>;
import Utility.IO.File;
import :Shader;

constinit static const GLchar* lastError = nullptr;
inline constexpr std::string_view noError = "No Error";

gl::Shader::Shader(shader::ShaderType sh_type)
noexcept
	: base()
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

	constexpr std::string_view ext_main{ "main" };
	const size_t off = contents.find(ext_main, 0);
	if (std::string::npos == off)
	{
		return shader::ErrorCode::NotValidShader;
	}

	return Compile(contents);
}

gl::shader::ErrorCode
gl::Shader::Compile(std::string_view content)
noexcept
{
	shader::ErrorCode result = shader::ErrorCode::Success;

	unsigned int shid = ::glCreateShader(static_cast<GLenum>(myType));
	if (NULL == shid)
	{
		fprintf(stderr, "Error creating shader type %d\n", myType);
	}

	return result;
}

void
gl::Shader::Use(const unsigned int& program)
noexcept
{
	::glUseShaderProgramEXT(static_cast<GLenum>(myType), GetID());
}

void
gl::Shader::Destroy()
noexcept
{
	if (IsLoaded() && IsCompiled())
	{
		::glDeleteShader(GetID());
		SetID(0);
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
	return IsCompiled() && myType != gl::shader::ShaderType::None;
}

bool
gl::Shader::IsUnloaded()
const noexcept
{
	return !IsCompiled() || myType == gl::shader::ShaderType::None;
}

bool
gl::Shader::IsCompiled()
const noexcept
{
	return isCompiled;
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
