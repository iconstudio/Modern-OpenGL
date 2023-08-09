export module Glib:SharedBufferObject;
import <memory>;
import :BufferObject;

export namespace gl
{
	class [[nodiscard]] SharedBufferObject
		: public gl::detail::BufferInterface<true>
	{
	public:
		using base = gl::detail::BufferInterface<true>;
		using blob_t = std::shared_ptr<float[]>;

		using base::base;

		~SharedBufferObject() = default;

		void Create(gl::buffer::BufferUsage usage, const size_t& bytes_size);

		SharedBufferObject(const SharedBufferObject&) = default;
		SharedBufferObject(SharedBufferObject&&) = default;
		SharedBufferObject& operator=(const SharedBufferObject&) = default;
		SharedBufferObject& operator=(SharedBufferObject&&) = default;

	private:
		blob_t myBlob;
	};
}
