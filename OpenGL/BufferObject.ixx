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
			None = 0,
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

		enum class [[nodiscard]] BufferUsage : std::uint32_t
		{
			None = 0,
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

	namespace detail
	{
		class
			alignas(std::hardware_constructive_interference_size)
			BufferImplement : public gl::Object
		{
		public:
			using base = gl::Object;

			~BufferImplement() noexcept;

			void SetData(const void* const& data, const size_t& size, buffer::BufferUsage usage) noexcept;
			void SetSubData(const void* const& src_data, const size_t& size, const ptrdiff_t& offset) noexcept;

			constexpr void SetLayout(const BufferLayout& layout) noexcept
			{
				myLayout = layout;
			}

			constexpr void SetLayout(BufferLayout&& layout) noexcept
			{
				myLayout = static_cast<BufferLayout&&>(layout);
			}

			void Bind() const noexcept;
			void Unbind() const noexcept;
			void Use() const noexcept;

			void CopyTo(BufferImplement& other, const size_t& dest_size, const ptrdiff_t& dest_offset = 0LL, const ptrdiff_t& offset = 0LL) const noexcept;

			[[nodiscard]] constexpr gl::buffer::BufferType GetType() const noexcept
			{
				return myType;
			}

			[[nodiscard]] constexpr gl::buffer::BufferUsage GetUsage() const noexcept
			{
				return myUsage;
			}

			[[nodiscard]] constexpr size_t GetSize() const noexcept
			{
				return mySize;
			}

			[[nodiscard]] constexpr const BufferLayout& GetLayout() const noexcept
			{
				return myLayout;
			}

			BufferImplement(const BufferImplement&) = delete;
			BufferImplement(BufferImplement&&) noexcept = default;
			BufferImplement& operator=(const BufferImplement&) = delete;
			BufferImplement& operator=(BufferImplement&&) noexcept = default;

		protected:
			BufferImplement() noexcept;
			BufferImplement(gl::buffer::BufferType buffer_type) noexcept;

			volatile gl::buffer::BufferType myType;
			volatile gl::buffer::BufferUsage myUsage;

			BufferLayout myLayout;
			size_t mySize;
		};

		template<bool provide_modifiable_layout>
		class BufferInterface;

		template<>
		class BufferInterface<true> : public BufferImplement
		{
		public:
			using base = BufferImplement;

			using base::base;

			[[nodiscard]] constexpr BufferLayout& GetLayout() noexcept
			{
				return myLayout;
			}
		};

		template<>
		class BufferInterface<false> : public BufferImplement
		{
		public:
			using base = BufferImplement;

			using base::base;
		};
	}

	class [[nodiscard]]
		alignas(std::hardware_constructive_interference_size)
			BufferObject : public gl::detail::BufferInterface<false>
	{
	public:
		using base = gl::detail::BufferInterface<false>;

		BufferObject(buffer::BufferType buffer_type = buffer::BufferType::Array) noexcept;
		~BufferObject() noexcept;

	};
}
