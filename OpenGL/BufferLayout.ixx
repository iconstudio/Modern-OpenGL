export module Glib:BufferLayout;
import <vector>;
import <tuple>;

template<typename T>
struct typename_table
{
	static inline constexpr int value = 0;
};

#define MAKE_TABLE_ENTRY(type, index) template<> struct typename_table<type> { static inline constexpr int value = index; };

MAKE_TABLE_ENTRY(bool, 0x1401); // GL_UNSIGNED_BYTE
MAKE_TABLE_ENTRY(std::int8_t, 0x1400); // GL_BYTE
MAKE_TABLE_ENTRY(std::uint8_t, 0x1401); // GL_UNSIGNED_BYTE
MAKE_TABLE_ENTRY(std::int16_t, 0x1402); // GL_SHORT
MAKE_TABLE_ENTRY(std::uint16_t, 0x1403); // GL_UNSIGNED_SHORT
MAKE_TABLE_ENTRY(std::int32_t, 0x1404); // GL_INT
MAKE_TABLE_ENTRY(std::uint32_t, 0x1405); // GL_UNSIGNED_INT
MAKE_TABLE_ENTRY(long, 0x1404); // GL_INT
MAKE_TABLE_ENTRY(unsigned long, 0x1405); // GL_UNSIGNED_INT
MAKE_TABLE_ENTRY(float, 0x1406); // GL_FLOAT
MAKE_TABLE_ENTRY(double, 0x140A); // GL_DOUBLE

template<typename T>
[[nodiscard]]
consteval int get_typeindex() noexcept
{
	return typename_table<T>::template value;
}

export namespace gl
{
#pragma warning(push)
#pragma warning(disable: 4324)
	class [[nodiscard]]
		alignas(std::hardware_constructive_interference_size)
		BufferLayout
	{
	public:
		using element_t = std::tuple<int, int, int, ptrdiff_t, bool>;

		constexpr BufferLayout() noexcept = default;
		~BufferLayout() noexcept = default;

		template<typename T>
		constexpr void AddElement(const int& count, const bool& normalized = false)
		{
			AddUnsafeElement<T>(count, count * sizeof(T), myStride, normalized);
		}

		template<typename T>
		constexpr void AddUnsafeElement(const int& count, const int& stride, const ptrdiff_t& offset, const bool& normalized = false)
		{
			myElements.emplace_back(count, get_typeindex<T>(), stride, offset, normalized);
			myStride += stride;
		}

		[[nodiscard]]
		constexpr element_t& Get(const size_t& index) noexcept
		{
			return myElements[index];
		}

		[[nodiscard]]
		constexpr const element_t& Get(const size_t& index) const noexcept
		{
			return myElements[index];
		}

		[[nodiscard]]
		constexpr const std::vector<element_t>& GetElements() const noexcept
		{
			return myElements;
		}

		[[nodiscard]]
		constexpr int GetStride() const noexcept
		{
			return myStride;
		}

		constexpr BufferLayout(const BufferLayout&) noexcept = default;
		constexpr BufferLayout(BufferLayout&&) noexcept = default;
		constexpr BufferLayout& operator=(const BufferLayout&) noexcept = default;
		constexpr BufferLayout& operator=(BufferLayout&&) noexcept = default;

	private:
		std::vector<element_t> myElements{};
		int myStride = 0;
	};
#pragma warning(pop)
}
