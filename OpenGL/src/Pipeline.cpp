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
volatile noexcept
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

bool
gl::Pipeline::Start()
const volatile noexcept
{
	if (not IsValid())
	{
		return false;
	}
	else
	{
		::glLinkProgram(GetID());
		return true;
	}
}

void
gl::Pipeline::Use()
volatile noexcept
{
	::glUseProgram(GetID());
}

void
gl::Pipeline::Render(Primitive pr, const std::uint32_t& vertices_count)
const volatile noexcept
{
	if (IsValid())
	{
		global::EmitPrimitives(pr, 0, vertices_count);
	}
}

void
gl::Pipeline::Destroy()
noexcept
{
	if (IsValid())
	{
		const std::uint32_t id = GetID();

		for (shader_handle_t& shader : myShaders)
		{
			::glDetachShader(id, shader->GetID());
		}
		::glDeleteProgram(id);
		SetID(NULL);
	}
}

void
gl::Pipeline::AddShader(shader_t&& shader)
{
	AddShader(std::make_unique<shader_t>(std::move(shader)));
}

void
gl::Pipeline::AddShader(shader_handle_t&& shader)
{
	::glAttachShader(myID, shader->GetID());

	myShaders.push_back(std::move(shader));
}

size_t
gl::Pipeline::GetNumberOfShaders()
const noexcept
{
	return myShaders.size();
}
