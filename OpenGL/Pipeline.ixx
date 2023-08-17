export module Glib:Pipeline;
import <memory>;
import <vector>;
import <functional>;
import :Object;
import :Shader;

export namespace gl
{
	class [[nodiscard]] Pipeline final : public gl::Object
	{
	private:
		using base = gl::Object;
		
	public:
		using shader_t = std::unique_ptr<gl::Shader>;
		using shader_handle_t = std::unique_ptr<shader_t>;
		using renderer_t = std::move_only_function<void() noexcept>;

		static inline constexpr size_t DefaultReservedShaders = 8;

		Pipeline() noexcept;
		~Pipeline() noexcept;

		void Awake() noexcept;
		void Use() noexcept;
		void Destroy() noexcept;

		void AddShader(shader_t&& shader);
		void AddShader(shader_handle_t&& shader);

		[[nodiscard]] size_t GetNumberOfShaders() const noexcept;

		Pipeline(const Pipeline&) = delete;
		Pipeline(Pipeline&&) noexcept = default;
		Pipeline& operator=(const Pipeline&) = delete;
		Pipeline& operator=(Pipeline&&) noexcept = default;

	private:
		std::vector<shader_t> myShaders;
	};
}
