export module Glib:BufferLayout;
import <vector>;
import <tuple>;

template<typename T>
struct typename_table
{
	static inline constexpr int value = 0;
};

#define MAKE_TABLE_ENTRY(type, index) template<> struct typename_table<type> { static inline constexpr int value = index; };

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
	class [[nodiscard]] BufferLayout
	{
	public:
		BufferLayout() noexcept = default;
		~BufferLayout() noexcept = default;

		template<typename T>
		void AddElement(const int& count, const bool& normalized) noexcept
		{
			AddUnsafeElement<T>(count, normalized, count * sizeof(T), myStride);
		}

		template<typename T>
		void AddUnsafeElement(const int& count, const bool& normalized, const int& stride, const int& offset) noexcept
		{
			myElements.emplace_back(count, get_typeindex<T>(), normalized, stride, offset);
			myStride += stride;
		}

		[[nodiscard]]
		constexpr const std::vector<std::tuple<int, int, bool, int, int>>& GetElements() const noexcept
		{
			return myElements;
		}

		[[nodiscard]]
		constexpr int GetStride() const noexcept
		{
			return myStride;
		}

	private:
		std::vector<std::tuple<int, int, bool, int, int>> myElements;
		int myStride = 0;
	};
}
