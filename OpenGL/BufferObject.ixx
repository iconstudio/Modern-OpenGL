export module Glib:BufferObject;
import <cstdint>;
import :Object;
export import :BufferLayout;

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

		enum class [[nodiscard]] BufferUsage
		{
			StaticDraw = 0x88E4,
			StaticRead = 0x88E5,
			StaticCopy = 0x88E6,
			DynamicDraw = 0x88E8,
			DynamicRead = 0x88E9,
			DynamicCopy = 0x88EA,
			StreamDraw = 0x88E0,
			StreamRead = 0x88E1,
			StreamCopy = 0x88E2
		};
	}

	class [[nodiscard]]
		alignas(std::hardware_constructive_interference_size)
		BufferObject : public gl::Object
	{
	public:
		using base = gl::Object;

		BufferObject();
		~BufferObject();

		void SetData(const void* const& data, const size_t& size, buffer::BufferUsage usage) noexcept;
		void SetSubData(const void* const& src_data, const size_t& size, const ptrdiff_t& offset) noexcept;
		void SetLayout(const BufferLayout& layout) noexcept;
		void SetLayout(BufferLayout&& layout) noexcept;

		void Bind() const noexcept;
		void Unbind() const noexcept;
		void Use() const noexcept;

		void CopyTo(BufferObject& other, const size_t& dest_size, const ptrdiff_t& dest_offset = 0LL, const ptrdiff_t& offset = 0LL) const noexcept;

		[[nodiscard]] buffer::BufferType GetType() const noexcept;
		[[nodiscard]] buffer::BufferUsage GetUsage() const noexcept;
		[[nodiscard]] const BufferLayout& GetLayout() const noexcept;
		[[nodiscard]] size_t GetSize() const noexcept;

		BufferObject(const BufferObject&) = delete;
		BufferObject(BufferObject&&) noexcept = default;
		BufferObject& operator=(const BufferObject&) = delete;
		BufferObject& operator=(BufferObject&&) noexcept = default;

	private:
		volatile buffer::BufferType myType = buffer::BufferType::Array;
		volatile buffer::BufferUsage myUsage = buffer::BufferUsage::StaticDraw;
		BufferLayout myLayout{};
		size_t mySize = 0;
	};
}
