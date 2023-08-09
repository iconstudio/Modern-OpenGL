export module Glib:VertexBuffer;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]]
		alignas(std::hardware_constructive_interference_size)
		VertexBuffer
	{
	public:
		VertexBuffer() noexcept;
		~VertexBuffer() noexcept = default;

		void Assign(const void* const& data, const size_t& size, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void SetLayout(const BufferLayout& layout) noexcept;
		void SetLayout(BufferLayout&& layout) noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;
		void Use() const noexcept;

		[[nodiscard]] buffer::BufferUsage GetUsage() const noexcept;
		[[nodiscard]] size_t GetSize() const noexcept;
		[[nodiscard]] BufferObject& GetHandle() noexcept;
		[[nodiscard]] const BufferObject& GetHandle() const noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) noexcept = default;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept = default;

	private:
		BufferObject myHandle;
	};
}
