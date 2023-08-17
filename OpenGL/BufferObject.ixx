export module Glib:BufferObject;
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
			constexpr BufferImplement() noexcept = default;
			virtual constexpr ~BufferImplement() noexcept = default;

			virtual void Create(buffer::BufferType buffer_type, buffer::BufferUsage usage, const void* data, const size_t& size) noexcept;
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

			constexpr BufferImplement(const BufferImplement&) noexcept = default;
			constexpr BufferImplement(BufferImplement&&) noexcept = default;
			constexpr BufferImplement& operator=(const BufferImplement&) noexcept = default;
			constexpr BufferImplement& operator=(BufferImplement&&) noexcept = default;

		protected:
			volatile buffer::BufferType myType = buffer::BufferType::None;
			volatile buffer::BufferUsage myUsage = buffer::BufferUsage::None;

			BufferLayout myLayout{};
			size_t mySize = 0;
		};
	}

	template<>
	class BufferInterface<true> : protected detail::BufferImplement
	{
	private:
		using base = detail::BufferImplement;

	public:
		using base::base;
		using base::Create;
		using base::Destroy;
		using base::CopyFrom;
		using base::CopyTo;
		using base::Swap;
		using base::SetLayout;
		using base::Bind;
		using base::Unbind;
		using base::Use;
		using base::GetType;
		using base::GetUsage;
		using base::GetLayout;
		using base::GetSize;

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

	public:
		using base::base;
		using base::Create;
		using base::Destroy;
		using base::CopyFrom;
		using base::CopyTo;
		using base::Swap;
		using base::SetLayout;
		using base::Bind;
		using base::Unbind;
		using base::Use;
		using base::GetType;
		using base::GetUsage;
		using base::GetLayout;
		using base::GetSize;
	};

	export class [[nodiscard]] BufferObject : public BufferInterface<false>
	{
	private:
		using base = BufferInterface<false>;

	public:
		constexpr BufferObject() noexcept = default;
		virtual ~BufferObject() noexcept;

		void Create(buffer::BufferType buffer_type, buffer::BufferUsage usage, const void* data, const size_t& size) noexcept override;

	private:

		volatile bool isAvailable;
	};
}
