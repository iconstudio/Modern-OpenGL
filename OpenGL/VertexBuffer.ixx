export module Glib:VertexBuffer;
import <cstdint>;
import <initializer_list>;
import <concepts>;
import <ranges>;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] VertexBuffer
		: public gl::detail::BufferInterface<true>
	{
	private:
		using base = gl::detail::BufferInterface<true>;

	public:
		VertexBuffer() noexcept;
		~VertexBuffer() noexcept = default;

		void Create(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void Create(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void Create(std::initializer_list<float> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		template<std::ranges::contiguous_range R>
		void Create(R&& buf, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) noexcept = default;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept = default;
	};

	template<std::ranges::contiguous_range R>
	void VertexBuffer::Create(R&& buf, buffer::BufferUsage usage) noexcept
	{
		static_assert(sizeof(std::ranges::range_value_t<R>) == sizeof(std::int32_t));

		base::Create(buf.data(), buf.size(), usage);
	}
}
