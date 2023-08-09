export module Glib:SharedBufferObject;
import <memory>;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] SharedBufferObject
		: public gl::detail::BufferInterface<false>
	{
	public:
		using base = gl::detail::BufferInterface<false>;
		using blob_t = std::shared_ptr<void>;

		SharedBufferObject(buffer::BufferType buffer_type = buffer::BufferType::Array);
		~SharedBufferObject() = default;

		void Create(buffer::BufferUsage usage, const size_t& bytes_size) noexcept;

		SharedBufferObject(const SharedBufferObject&) = default;
		SharedBufferObject(SharedBufferObject&&) = default;
		SharedBufferObject& operator=(const SharedBufferObject&) = default;
		SharedBufferObject& operator=(SharedBufferObject&&) = default;

	private:
		blob_t myBlob;
	};
}
