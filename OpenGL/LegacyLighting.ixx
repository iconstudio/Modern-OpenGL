export module Glib.Legacy.Lighting;
import <cstdint>;
import Glib;
import Glib.Windows.Colour;

export namespace gl::legacy
{
	using ::gl::win32::Colour;

	enum [[nodiscard]] ShadeModel : std::uint32_t
	{
		Flat = 0x1D00U,
		Smooth = 0x1D01U
	};

	enum [[nodiscard]] LightOption : std::int32_t
	{
		LocalViewer = 0x0B51,
		TwoSide = 0x0B52,
	};

	enum [[nodiscard]] LightModel : std::uint32_t
	{
		Ambient = 0x1200U,
		Diffuse = 0x1201U,
		Specular = 0x1202U,
	};

	struct [[nodiscard]] Material
	{
		Colour ambient;
		Colour diffuse;
		Colour specular;
		Colour emission;

		std::int32_t shininess = 32;
	};

	struct [[nodiscard]] Light
	{
		Colour ambient{};
		Colour diffuse{ 1.0, 1.0, 1.0 };
		Colour specular{};
		//Position position{};
		//Direction direction{};

		float spotExponent = 0.0f;
		float spotCutoff = 180.0f;

		float constantAttenuation = 1.0f;
		float linearAttenuation = 0.0f;
		float quadraticAttenuation = 0.0f;
	};

	class Caster
	{
	public:
		Caster() noexcept;
		~Caster() noexcept;

		void SetType(LightModel type) noexcept;
		void SetShadeModel(ShadeModel shade) noexcept;
		void SetOption(LightOption option, bool value) noexcept;
		void SetColor(const Colour& colour) noexcept;
		void SetColor(Colour&& colour) noexcept;
		void SetMaterial(const Material& material) noexcept;
		void SetMaterial(Material&& material) noexcept;

		void Assign(const Light& light) noexcept;
		void Assign(Light&& light) noexcept;

		void Enable() noexcept;
		void Disable() noexcept;

		[[nodiscard]] Light& GetLight() noexcept;
		[[nodiscard]] const Light& GetLight() const noexcept;

		Caster(const Caster&) = delete;
		Caster(Caster&&) = delete;
		Caster& operator=(const Caster&) = delete;
		Caster& operator=(Caster&&) = delete;

	private:
		std::uint32_t myIndex;
	};
}

export namespace gl
{
	using LegacyMaterial = ::gl::legacy::Material;
	using LegacyLight = ::gl::legacy::Light;
	using LegacyCaster = ::gl::legacy::Caster;
}
