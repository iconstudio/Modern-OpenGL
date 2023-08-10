export module Glib:IndexBuffer;
import <cstdint>;
import <initializer_list>;
import <concepts>;
import <ranges>;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] IndexBuffer : public gl::BufferInterface<true>
	{
	private:
		using base = gl::BufferInterface<true>;

	public:
		IndexBuffer() noexcept;
		~IndexBuffer() noexcept = default;

		void Create(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		void Create(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;
		template<std::ranges::contiguous_range R>
		void Create(R&& buf, buffer::BufferUsage usage = buffer::BufferUsage::StaticDraw) noexcept;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) noexcept = default;
		IndexBuffer& operator=(const IndexBuffer&) = delete;
		IndexBuffer& operator=(IndexBuffer&&) noexcept = default;
	};

	template<std::ranges::contiguous_range R>
	void IndexBuffer::Create(R&& buf, buffer::BufferUsage usage) noexcept
	{
		static_assert(sizeof(std::ranges::range_value_t<R>) == sizeof(std::int32_t));

		base::Create(buffer::BufferType::ElementArray, buf.data(), buf.size(), usage);
	}
}
