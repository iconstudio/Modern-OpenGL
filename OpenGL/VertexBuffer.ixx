export module Glib:VertexBuffer;
import <cstdint>;
import :BufferObject;

export namespace gl
{
	namespace buffer
	{
		enum class [[nodiscard]] BufferType : std::uint32_t
		{
			Vertex = 0x8892,
			Array = Vertex,
			Index = 0x8893,
			ElementArray = Index,
			Uniform = 0x8A11,
			PixelPack = 0x88EB,
			PixelUnpack = 0x88EC,
			Texture = 0x8C2A,
			TransformFeedback = 0x8C8E,
			CopyRead = 0x8F36,
			CopyWrite = 0x8F37,
			DrawIndirect = 0x8F3F,

			AtomicCounter = 0x92C0,
			ShaderStorage = 0x90D2,
			DispatchIndirect = 0x90EE,
			Query = 0x9192
		};
	}

	class [[nodiscard]] VertexBuffer : public BufferObject
	{
	public:
		using base = BufferObject;

		VertexBuffer();
		~VertexBuffer();

		void SetData(const void* const& data, const size_t& size, buffer::BufferType usage) const noexcept;
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
		buffer::BufferType myType = buffer::BufferType::Vertex;
		//VertexLayout m_Layout;
		size_t mySize = 0;
	};
}
