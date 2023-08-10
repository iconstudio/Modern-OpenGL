export module Glib:BufferObject;
import <cstdint>;
import :Object;
export import :BufferType;
export import :BufferUsage;
export import :BufferLayout;

namespace gl
{
	export template<bool provide_modifiable_layout>
		class BufferInterface;

	namespace detail
	{
		class alignas(std::hardware_constructive_interference_size)
			BufferImplement : protected gl::Object
		{
		private:
			using base = gl::Object;

		public:
			~BufferImplement() noexcept;

			void Create(const void* const& data, const size_t& size, buffer::BufferUsage usage) noexcept;
			void Destroy();

			void CopyFrom(const void* const& src_data, const size_t& size, const ptrdiff_t& offset) noexcept;
			void CopyTo(BufferImplement& other, const size_t& dest_size, const ptrdiff_t& dest_offset = 0LL, const ptrdiff_t& offset = 0LL) const noexcept;
		
			constexpr void Swap(BufferImplement& other) noexcept
			{
				std::swap(myType, other.myType);
				std::swap(myUsage, other.myUsage);
				std::swap(myLayout, other.myLayout);
				std::swap(mySize, other.mySize);
			}

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
	}

	template<>
	class BufferInterface<true> : protected detail::BufferImplement
	{
	private:
		using base = detail::BufferImplement;
		operator BufferImplement() = delete;

	public:
		using base::base;
		using base::Create;
		using base::CopyFrom;
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
	class BufferInterface<false> : protected detail::BufferImplement
	{
	private:
		using base = detail::BufferImplement;
		operator BufferImplement() = delete;

	public:
		using base::base;
		using base::Create;
		using base::CopyFrom;
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

	export class [[nodiscard]] BufferObject : public BufferInterface<false>
	{
	private:
		using base = BufferInterface<false>;

	public:
		BufferObject(buffer::BufferType buffer_type) noexcept;
		~BufferObject() noexcept = default;
	};
}
