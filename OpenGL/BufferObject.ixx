export module Glib:BufferObject;
import <cstdint>;

export namespace gl
{
	class [[nodiscard]] BufferObject
	{
		static inline constexpr std::uint32_t npos = static_cast<std::uint32_t>(-1);

	public:
		[[nodiscard]] constexpr std::uint32_t GetID() const noexcept
		{
			return myID;
		}

		[[nodiscard]] constexpr bool IsValid() const noexcept
		{
			return myID != npos;
		}

	protected:
		constexpr BufferObject() noexcept = default;
		constexpr ~BufferObject() noexcept = default;

		explicit constexpr BufferObject(std::uint32_t id) noexcept
			: myID(id)
		{}

		std::uint32_t myID = npos;
		void* myData = nullptr;
	};
}
