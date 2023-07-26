export module Glib.Legacy.Lighting;
import <cstdint>;
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

	enum [[nodiscard]] LightComponent : std::uint32_t
	{
		None = 0U,
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
		Colour diffuse{ 1.0f, 1.0f, 1.0f };
		Colour specular{};
		float position[3]{};

		float spotExponent = 0.0f;
		float spotCutoff = 180.0f;
		float spotDirection[3]{};

		float constantAttenuation = 1.0f;
		float linearAttenuation = 0.0f;
		float quadraticAttenuation = 0.0f;
	};

	class Caster
	{
	public:
		Caster();
		~Caster() noexcept;

		void SetShadeModel(ShadeModel shade) noexcept;
		void SetOption(LightOption option, bool value) noexcept;
		void SetAmbient(const Colour& colour) noexcept;
		void SetAmbient(Colour&& colour) noexcept;
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
		std::uint32_t myIndex = 0U;

		float cachedAmbient[4]{};
		float cachedDiffuse[4]{};
		float cachedSpecular[4]{};
		float cachedEmission[4]{};
	};
}

export namespace gl
{
	using LegacyMaterial = legacy::Material;
	using LegacyLight = legacy::Light;
	using LegacyCaster = legacy::Caster;
}
