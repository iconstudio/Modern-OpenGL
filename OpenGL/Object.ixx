export module Glib:Object;
import <cstdint>;

export namespace gl
{
	class [[nodiscard]] Object
	{
		static inline constexpr std::uint32_t npos = static_cast<std::uint32_t>(-1);

	public:
		[[nodiscard]]
		constexpr std::uint32_t GetID() const noexcept
		{
			return myID;
		}

		[[nodiscard]]
		constexpr bool IsValid() const noexcept
		{
			return myID != npos;
		}

	protected:
		constexpr Object() noexcept = default;
		constexpr ~Object() noexcept = default;

		explicit constexpr Object(std::uint32_t id) noexcept
			: myID(id)
		{}

		constexpr void SetID(const std::uint32_t& id) noexcept
		{
			myID = id;
		}

		constexpr void SetID(std::uint32_t&& id) noexcept
		{
			myID = static_cast<std::uint32_t&&>(id);
		}

		std::uint32_t myID = npos;
	};
}
