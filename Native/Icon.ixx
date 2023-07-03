module;
#include "Internal.hpp"
#undef LoadIcon
#undef DrawIcon

export module Glib.Device.Resource.Icon;
import <type_traits>;
import <string_view>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device::resource
{
	class [[nodiscard]] Icon : public IHandle<native::RawIcon>
	{
	protected:
		using base = IHandle<native::RawIcon>;

		constexpr Icon(handle_type&& icon, const unsigned int& length) noexcept
			: base(std::move(icon))
			, myLength(length)
		{}

	public:
		[[nodiscard]]
		friend Icon LoadIcon(const FilePath& path) noexcept;
		[[nodiscard]]
		friend bool TryLoadIcon(const FilePath& path, Icon& output) noexcept;
		[[nodiscard]]
		friend Icon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept;
		[[nodiscard]]
		friend bool TryLoadIconAt(const FilePath& path, const unsigned int& index, Icon& output) noexcept;
		[[nodiscard]]
		friend Icon LoadResource(const std::wstring_view& name) noexcept;
		[[nodiscard]]
		friend bool TryLoadResource(const std::wstring_view& name, Icon& output) noexcept;
		[[nodiscard]]
		friend Icon LoadResource(const int& id) noexcept;
		[[nodiscard]]
		friend bool TryLoadResource(const int& id, Icon& output) noexcept;
		[[nodiscard]]
		friend Icon CopyIcon(const Icon& icon) noexcept;
		[[nodiscard]]
		friend bool TryCopyIcon(const Icon& icon, Icon& output) noexcept;
		friend bool DrawIcon(const Icon& icon, const ::HDC& hdc, const int& x, const int& y) noexcept;
		friend bool DestroyIcon(Icon& icon) noexcept;

		constexpr Icon(nullptr_t) noexcept
			: base(nullptr)
			, myLength(0U)
		{}

		Icon& operator=(nullptr_t) noexcept;

		~Icon() noexcept;

		[[nodiscard]]
		Icon Copy() const noexcept;

		[[nodiscard]]
		bool TryCopy(Icon& output) const noexcept;

		bool Draw(const native::NativeSurface& hdc, const int& x, const int& y) const noexcept;

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

		Icon(const Icon&) = delete;
		constexpr Icon(Icon&&) noexcept = default;
		Icon& operator=(const Icon&) = delete;
		constexpr Icon& operator=(Icon&&) noexcept = default;

	private:
		unsigned int myLength;
	};
}

export namespace gl::device
{
	resource::Icon MakeEmptyIcon() noexcept;
}
