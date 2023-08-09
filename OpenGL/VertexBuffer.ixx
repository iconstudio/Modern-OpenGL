export module Glib:VertexBuffer;
import <cstdint>;
import <initializer_list>;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] VertexBuffer
		: public gl::detail::BufferInterface<true>
	{
	public:
		using base = gl::detail::BufferInterface<true>;

		VertexBuffer() noexcept;
		~VertexBuffer() noexcept = default;

		void Assign(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void Assign(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void Assign(std::initializer_list<float> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) noexcept = default;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept = default;
	};
}
