module;
#include <Windows.h>
#include "glew.h"
#include <GL/GL.h>

module Glib;
import <cstdint>;
import <type_traits>;
import :Pipeline;

gl::Pipeline::Pipeline()
noexcept
	: Pipeline(gl::noopt)
{
	(void)Awake();
}

gl::Pipeline::~Pipeline()
noexcept
{
	Destroy();
}

bool
gl::Pipeline::Awake()
noexcept
{
	const std::uint32_t id = ::glCreateProgram();
	if (NULL == id)
	{
		return false;
	}
	else
	{
		base::SetID(id);
		return true;
	}
}

void
gl::Pipeline::Use()
noexcept
{}

void
gl::Pipeline::Destroy()
noexcept
{
	if (IsValid())
	{
		::glDeleteProgram(myID);
		SetID(base::npos);
	}
}

void
gl::Pipeline::AddShader(shader_t&& shader)
{
	myShaders.emplace_back(std::move(shader));
}

void
gl::Pipeline::AddShader(shader_handle_t&& shader)
{
	myShaders.push_back(std::move(shader));
}

size_t
gl::Pipeline::GetNumberOfShaders()
const noexcept
{
	return size_t();
}
