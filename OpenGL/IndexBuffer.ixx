export module Glib:IndexBuffer;
import <cstdint>;
import <initializer_list>;
import <concepts>;
import <ranges>;
import :BufferObject;
import Utility.Constraints;

export namespace gl
{
	class [[nodiscard]] IndexBuffer
		: public gl::detail::BufferInterface<true>
	{
	public:
		using base = gl::detail::BufferInterface<true>;

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

		base::Create(buf.data(), buf.size(), usage);
	}
}
