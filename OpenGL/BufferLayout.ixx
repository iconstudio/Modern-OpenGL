export module Glib:BufferLayout;
import <vector>;
import <tuple>;

template<typename T>
struct typename_table
{
	static inline constexpr int value = 0;
};

#define MAKE_TABLE_ENTRY(type, index) template<> struct typename_table<type> { static inline constexpr int value = index; };

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
			myElements.emplace_back(count, type, normalized, myStride, 0);
			myStride += count * sizeof(type);
		}

		void AddElement(const int& count, const int& type, const bool& normalized, const int& stride, const int& offset) noexcept
		{
			myElements.emplace_back(count, type, normalized, stride, offset);
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
