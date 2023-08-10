export module Glib:BufferObject;
import <cstdint>;
import :Object;
export import :BufferType;
export import :BufferUsage;
export import :BufferLayout;

export namespace gl
{
	namespace detail
	{
		class
			alignas(std::hardware_constructive_interference_size)
			BufferImplement : protected gl::Object
		{
		private:
			using base = gl::Object;

		public:
			~BufferImplement() noexcept;

			void Create(const void* const& data, const size_t& size, buffer::BufferUsage usage) noexcept;

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

			[[nodiscard]] constexpr buffer::BufferType GetType() const noexcept
			{
				return myType;
			}

			[[nodiscard]] constexpr buffer::BufferUsage GetUsage() const noexcept
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
			BufferImplement(buffer::BufferType buffer_type) noexcept;

			volatile buffer::BufferType myType;
			volatile buffer::BufferUsage myUsage;

			BufferLayout myLayout;
			size_t mySize;
		};

		template<bool provide_modifiable_layout>
		class BufferInterface;

		template<>
		class BufferInterface<true> : protected BufferImplement
		{
		private:
			using base = BufferImplement;
			operator BufferImplement() = delete;

		public:
			using base::base;
			using base::Create;
			using base::SetSubData;
			using base::SetLayout;
			using base::Bind;
			using base::Unbind;
			using base::Use;
			using base::GetType;
			using base::GetUsage;
			using base::GetLayout;
			using base::GetSize;
			using base::CopyTo;

			[[nodiscard]] constexpr BufferLayout& GetLayout() noexcept
			{
				return myLayout;
			}
		};

		template<>
		class BufferInterface<false> : protected BufferImplement
		{
		private:
			using base = BufferImplement;
			operator BufferImplement() = delete;

		public:
			using base::base;
			using base::Create;
			using base::SetSubData;
			using base::SetLayout;
			using base::Bind;
			using base::Unbind;
			using base::Use;
			using base::GetType;
			using base::GetUsage;
			using base::GetLayout;
			using base::GetSize;
			using base::CopyTo;
		};
	}

	class [[nodiscard]] BufferObject
		: public detail::BufferInterface<false>
	{
	private:
		using base = detail::BufferInterface<false>;

	public:
		BufferObject(buffer::BufferType buffer_type) noexcept;
		~BufferObject() noexcept = default;
	};
}
