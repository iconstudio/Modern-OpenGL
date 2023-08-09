export module Glib.Buffer;
import <cstdint>;
import Glib;

export namespace gl
{
	enum class BufferType : std::uint32_t
	{
		invalid = static_cast<std::uint32_t>(-1),
	};

	class [[nodiscard]] Buffer : public Object
	{
	public:
		Buffer() = default;
		~Buffer() = default;

		void Create(const void* const& data, size_t size, BufferType usage) const noexcept;
		void SetSubData(const void* const& data, size_t size, size_t offset) const noexcept;
		void ClearData(std::uint32_t internalformat, std::uint32_t format, std::uint32_t type, const void* const& data) const noexcept;
		void CopySubData(const Buffer& readBuffer, size_t readOffset, size_t writeOffset, size_t size);

		void Bind() const noexcept;
		void Unbind() const noexcept;

		void* Map(std::uint32_t access) const noexcept;
		void* MapRange(std::uintptr_t offset, std::uintptr_t length, std::uint8_t access) const noexcept;
		void Unmap() const noexcept;

		void GetPointer(std::uint32_t pname, void** params) const noexcept;
		void GetSubData(void* data, size_t size, size_t offset) const noexcept;
		void GetParameter(std::uint32_t pname, std::uint32_t* params) const noexcept;
		void GetParameter(std::uint32_t pname, std::uint64_t* params) const noexcept;

		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) noexcept = default;
		Buffer& operator=(const Buffer&) = delete;
		Buffer& operator=(Buffer&&) noexcept = default;

	private:
		std::uint32_t myTarget{ 0 };
	};
}
