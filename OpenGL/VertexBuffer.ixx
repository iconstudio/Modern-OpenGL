export module Glib:VertexBuffer;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] VertexBuffer : public BufferObject
	{
	public:
		using base = BufferObject;

		VertexBuffer();
		~VertexBuffer();

		void SetData(const void* data, size_t size, unsigned int usage) const noexcept;
		void SetSubData(const void* const& src_data, const size_t& size, const size_t& offset) const noexcept;
		void SetLayout(const int& layout) const noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;
		void Use() const noexcept;

		void CopyTo(VertexBuffer& other, size_t size, size_t srcOffset, size_t dstOffset) const noexcept;

		//const VertexLayout& GetLayout() const noexcept;
		//static void UnbindAll() noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) noexcept = default;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept = default;

	private:
		//VertexLayout m_Layout;
		size_t mySize = 0;
	};
}
