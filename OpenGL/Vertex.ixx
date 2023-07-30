export module Glib:Vertex;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] VertexBuffer : public BufferObject
	{
	public:
		VertexBuffer() noexcept;
		~VertexBuffer() noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;

		void SetData(const void* data, size_t size, unsigned int usage) const noexcept;
		void SetSubData(const void* data, size_t size, size_t offset) const noexcept;
		void SetLayout(const int& layout) const noexcept;
		
		//const VertexLayout& GetLayout() const noexcept;
		//static void UnbindAll() noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) noexcept = default;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept = default;
	};
}
