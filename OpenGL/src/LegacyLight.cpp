module;
#include <Windows.h>
#include <gl\gl.h>

module Glib.Legacy.Lighting;
import <stdexcept>;
import <type_traits>;
import <array>;
import <unordered_set>;

constexpr std::uint32_t	maxLights = GL_MAX_LIGHTS;
constexpr std::uint32_t firstLightIndex = GL_LIGHT0;
constexpr std::uint32_t lastLightIndex = firstLightIndex + maxLights;

static std::array<gl::legacy::Light, maxLights> everyLights{};
static std::unordered_set<std::uint32_t> enabledLights{};
static std::uint32_t nextLightIndex = GL_LIGHT0;

void EnableLight() noexcept;
void EnableLight(bool flag) noexcept;
void DisableLight() noexcept;

[[nodiscard]] gl::legacy::Light& AcquireLight(std::uint32_t index);
bool TryAcquireLight(std::uint32_t index, gl::legacy::Light& light) noexcept;

gl::legacy::Caster::Caster()
	: myIndex(nextLightIndex)
{
	if (enabledLights.size() == maxLights)
	{
		throw std::runtime_error("Too many lights enabled");
	}

	if (enabledLights.empty())
	{
		EnableLight();
	}

	enabledLights.insert(nextLightIndex++);
	Enable();
}

gl::legacy::Caster::~Caster()
noexcept
{
	Disable();

	enabledLights.erase(myIndex);
	if (enabledLights.empty())
	{
		DisableLight();
	}
}

void
gl::legacy::Caster::SetType(gl::legacy::LightModel type)
noexcept
{}

void
gl::legacy::Caster::SetShadeModel(gl::legacy::ShadeModel shade)
noexcept
{}

void
gl::legacy::Caster::SetOption(gl::legacy::LightOption option, bool value)
noexcept
{}

void
gl::legacy::Caster::SetColor(const gl::legacy::Colour& colour)
noexcept
{}

void
gl::legacy::Caster::SetColor(gl::legacy::Colour&& colour)
noexcept
{}

void
gl::legacy::Caster::SetMaterial(const gl::legacy::Material& material)
noexcept
{}

void
gl::legacy::Caster::SetMaterial(gl::legacy::Material&& material)
noexcept
{}

void
gl::legacy::Caster::Assign(const gl::legacy::Light& light)
noexcept
{}

void
gl::legacy::Caster::Assign(gl::legacy::Light&& light)
noexcept
{}

void
gl::legacy::Caster::Enable()
noexcept
{
	::glEnable(myIndex);
}

void
gl::legacy::Caster::Disable()
noexcept
{
	::glDisable(myIndex);
}

void
EnableLight()
noexcept
{
	EnableLight(true);
}

void
EnableLight(bool flag)
noexcept
{
	if (flag)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}

void
DisableLight()
noexcept
{
	EnableLight(false);
}

gl::legacy::Light&
AcquireLight(std::uint32_t index)
{
	if (index < firstLightIndex || lastLightIndex <= index)
	{
		throw std::runtime_error("Invalid light index");
	}

	return everyLights[index - firstLightIndex];
}

bool
TryAcquireLight(std::uint32_t index, gl::legacy::Light& light)
noexcept
{
	if (index < firstLightIndex || lastLightIndex <= index)
	{
		return false;
	}

	light = everyLights[index - firstLightIndex];
	return true;
}
