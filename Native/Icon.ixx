export module Glib.Device.Resource.Icon;
import <type_traits>;
import <string_view>;
import Glib.Device.Definitions;
import Glib.Device.IGraphics;

export namespace gl::device::resource
{
	class [[nodiscard]] Icon : public IGraphics<Icon, native::RawIcon>
	{
	public:
		using base = IGraphics<Icon, native::RawIcon>;

		[[nodiscard]]
		friend Icon LoadIcon(const FilePath& path) noexcept;
		[[nodiscard]]
		friend bool TryLoadIcon(const FilePath& path, Icon& output) noexcept;
		[[nodiscard]]
		friend Icon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept;
		[[nodiscard]]
		friend bool TryLoadIconAt(const FilePath& path, const unsigned int& index, Icon& output) noexcept;
		[[nodiscard]]
		friend Icon LoadIcon(const int& id) noexcept;
		[[nodiscard]]
		friend bool TryLoadIcon(const int& id, Icon& output) noexcept;

		constexpr Icon(nullptr_t) noexcept
			: base(nullifier)
			, myLength(0U)
		{}

		~Icon() noexcept;

		[[nodiscard]]
		Icon Copy() const noexcept;

		[[nodiscard]]
		bool TryCopy(Icon& output) const noexcept;

		bool Draw(const native::NativeContext& hdc, const int& x, const int& y) const noexcept;

		bool Destroy() noexcept;

		[[nodiscard]]
		constexpr unsigned int GetLength() const noexcept
		{
			return myLength;
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept
		{
			return nullptr == GetHandle();
		}

		Icon& operator=(nullptr_t) noexcept;

		Icon(const Icon&) = delete;
		constexpr Icon(Icon&&) noexcept = default;
		Icon& operator=(const Icon&) = delete;
		constexpr Icon& operator=(Icon&&) noexcept = default;

	protected:
		constexpr Icon(handle_type&& icon, const unsigned int& length) noexcept
			: base(std::move(icon))
			, myLength(length)
		{}

	private:
		unsigned int myLength;
	};
}

export namespace gl::device
{
	resource::Icon MakeEmptyIcon() noexcept;
}
