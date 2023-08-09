export module Glib:IndexBuffer;
import <cstdint>;
import <initializer_list>;
import <array>;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] IndexBuffer 
		: public gl::detail::BufferInterface<true>
	{
	public:
		using base = gl::detail::BufferInterface<true>;

		IndexBuffer() noexcept;
		~IndexBuffer() noexcept = default;

		void Assign(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void Assign(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) noexcept = default;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&&) noexcept = default;
	};
}
