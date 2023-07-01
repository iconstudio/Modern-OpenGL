module;
#include "Internal.hpp"
#undef LoadIcon
#undef DrawIcon

export module Glib.Device.Resource.Icon;
export import <string_view>;
import :Implement;

export namespace gl::device::resource
{
	using detail::RawIcon;

	class [[nodiscard]] Icon
	{
	protected:
		constexpr Icon(const RawIcon& icon, const unsigned int& length) noexcept
			: myIcon(icon)
			, myLength(length)
		{}

		constexpr Icon(RawIcon&& icon, const unsigned int& length) noexcept
			: myIcon(static_cast<RawIcon&&>(icon))
			, myLength(length)
		{}

	public:
		[[nodiscard]]
		friend Icon MakeEmptyIcon() noexcept;
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

		constexpr Icon(nullptr_t) noexcept
			: myIcon(nullptr)
			, myLength(0U)
		{}

		constexpr Icon& operator=(nullptr_t) noexcept
		{
			if (nullptr != myIcon)
			{
				detail::Destroy(myIcon);
			}
			myLength = 0U;

			return *this;
		}

		virtual inline ~Icon() noexcept
		{
			if (nullptr != myIcon)
			{
				detail::Destroy(myIcon);
			}
			myLength = 0U;
		}

		[[nodiscard]]
		Icon Copy() const noexcept
		{
			return CopyIcon(*this);
		}

		[[nodiscard]]
		bool TryCopy(Icon& output) const noexcept
		{
			return TryCopyIcon(*this, output);
		}

		bool Draw(const ::HDC& hdc, const int& x, const int& y) const noexcept
		{
			return DrawIcon(*this, hdc, x, y);
		}

		[[nodiscard]]
		constexpr const RawIcon& GetHandle() const& noexcept
		{
			return myIcon;
		}

		[[nodiscard]]
		constexpr RawIcon&& GetHandle() && noexcept
		{
			return static_cast<RawIcon&&>(myIcon);
		}

		[[nodiscard]]
		constexpr unsigned int GetLength() const noexcept
		{
			return myLength;
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept
		{
			return nullptr == myIcon;
		}

		Icon(const Icon&) = delete;
		constexpr Icon(Icon&&) noexcept = default;
		Icon& operator=(const Icon&) = delete;
		constexpr Icon& operator=(Icon&&) = default;

	private:
		RawIcon myIcon;
		unsigned int myLength;
	};

	Icon MakeEmptyIcon() noexcept
	{
		return Icon(nullptr, 0U);
	}

	Icon LoadIcon(const FilePath& path) noexcept
	{
		return Icon(detail::ExtractFrom(path, 0), detail::GetIconsNumber(path));
	}

	bool TryLoadIcon(const FilePath& path, Icon& output) noexcept
	{
		if (nullptr != detail::ExtractFrom(path, 0))
		{
			output.myLength = detail::GetIconsNumber(path);
			return true;
		}
		else
		{
			return false;
		}
	}

	Icon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept
	{
		return Icon(detail::ExtractFrom(path, index), detail::GetIconsNumber(path));
	}

	bool TryLoadIconAt(const FilePath& path, const unsigned int& index, Icon& output) noexcept
	{
		if (nullptr != detail::ExtractFrom(path, index))
		{
			output.myLength = detail::GetIconsNumber(path);
			return true;
		}
		else
		{
			return false;
		}
	}

	Icon LoadResource(const std::wstring_view& name) noexcept
	{
		return Icon(detail::LoadResource(name), 1);
	}

	bool TryLoadResource(const std::wstring_view& name, Icon& output) noexcept
	{
		if (detail::TryLoadResource(output.myIcon, name))
		{
			output.myLength = 1;
			return true;
		}
		else
		{
			return false;
		}
	}

	Icon LoadResource(const int& id) noexcept
	{
		return Icon(detail::LoadResource(id), 1);
	}

	bool TryLoadResource(const int& id, Icon& output) noexcept
	{
		if (detail::TryLoadResource(output.myIcon, id))
		{
			output.myLength = 1;
			return true;
		}
		else
		{
			return false;
		}
	}

	Icon CopyIcon(const Icon& icon) noexcept
	{
		return Icon(detail::Copy(icon.myIcon), icon.myLength);
	}

	bool TryCopyIcon(const Icon& icon, Icon& output) noexcept
	{
		if (detail::TryCopy(icon.myIcon, output.myIcon))
		{
			output.myLength = icon.myLength;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DrawIcon(const Icon& icon, const ::HDC& hdc, const int& x, const int& y) noexcept
	{
		return detail::Draw(icon.GetHandle(), hdc, x, y);
	}
}

export namespace gl::device
{
	using resource::MakeEmptyIcon;
}
