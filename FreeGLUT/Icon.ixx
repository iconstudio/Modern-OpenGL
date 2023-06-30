module;
#include "Internal.hpp"
#undef LoadIcon
#undef DrawIcon

export module Glib.Device.Resource.Icon;
export import <string_view>;
import :Implement;

export namespace gl::device::resource
{
	class [[nodiscard]] DeviceIcon
	{
	protected:
		constexpr DeviceIcon(const HICON& icon, const unsigned int& length) noexcept
			: myIcon(icon)
			, myLength(length)
		{}

		constexpr DeviceIcon(HICON&& icon, const unsigned int& length) noexcept
			: myIcon(static_cast<HICON&&>(icon))
			, myLength(length)
		{}

	public:
		[[nodiscard]]
		friend DeviceIcon MakeEmptyIcon() noexcept;
		[[nodiscard]]
		friend DeviceIcon LoadIcon(const FilePath& path) noexcept;
		[[nodiscard]]
		friend bool TryLoadIcon(const FilePath& path, DeviceIcon& output) noexcept;
		[[nodiscard]]
		friend DeviceIcon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept;
		[[nodiscard]]
		friend bool TryLoadIconAt(const FilePath& path, const unsigned int& index, DeviceIcon& output) noexcept;
		[[nodiscard]]
		friend DeviceIcon LoadResource(const std::wstring_view& name) noexcept;
		[[nodiscard]]
		friend bool TryLoadResource(const std::wstring_view& name, DeviceIcon& output) noexcept;
		[[nodiscard]]
		friend DeviceIcon LoadResource(const int& id) noexcept;
		[[nodiscard]]
		friend bool TryLoadResource(const int& id, DeviceIcon& output) noexcept;
		[[nodiscard]]
		friend DeviceIcon CopyIcon(const DeviceIcon& icon) noexcept;
		[[nodiscard]]
		friend bool TryCopyIcon(const DeviceIcon& icon, DeviceIcon& output) noexcept;
		friend bool DrawIcon(const DeviceIcon& icon, const ::HDC& hdc, const int& x, const int& y) noexcept;

		virtual inline ~DeviceIcon() noexcept
		{
			if (nullptr != myIcon)
			{
				detail::Destroy(myIcon);
			}
		}

		[[nodiscard]]
		DeviceIcon Copy() const noexcept
		{
			return CopyIcon(*this);
		}

		[[nodiscard]]
		bool TryCopy(DeviceIcon& output) const noexcept
		{
			return TryCopyIcon(*this, output);
		}

		bool Draw(const ::HDC& hdc, const int& x, const int& y) const noexcept
		{
			return DrawIcon(*this, hdc, x, y);
		}

		[[nodiscard]]
		constexpr const HICON& GetHandle() const& noexcept
		{
			return myIcon;
		}

		[[nodiscard]]
		constexpr HICON&& GetHandle() && noexcept
		{
			return static_cast<HICON&&>(myIcon);
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

		DeviceIcon(const DeviceIcon&) = delete;
		constexpr DeviceIcon(DeviceIcon&&) noexcept = default;
		DeviceIcon& operator=(const DeviceIcon&) = delete;
		constexpr DeviceIcon& operator=(DeviceIcon&&) = default;

	private:
		HICON myIcon;
		unsigned int myLength;
	};

	DeviceIcon MakeEmptyIcon() noexcept
	{
		return DeviceIcon(nullptr, 0U);
	}

	DeviceIcon LoadIcon(const FilePath& path) noexcept
	{
		return DeviceIcon(detail::ExtractFrom(path, 0), detail::GetIconsNumber(path));
	}

	bool TryLoadIcon(const FilePath& path, DeviceIcon& output) noexcept
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

	DeviceIcon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept
	{
		return DeviceIcon(detail::ExtractFrom(path, index), detail::GetIconsNumber(path));
	}

	bool TryLoadIconAt(const FilePath& path, const unsigned int& index, DeviceIcon& output) noexcept
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

	DeviceIcon LoadResource(const std::wstring_view& name) noexcept
	{
		return DeviceIcon(detail::LoadResource(name), 1);
	}

	bool TryLoadResource(const std::wstring_view& name, DeviceIcon& output) noexcept
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

	DeviceIcon LoadResource(const int& id) noexcept
	{
		return DeviceIcon(detail::LoadResource(id), 1);
	}

	bool TryLoadResource(const int& id, DeviceIcon& output) noexcept
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

	DeviceIcon CopyIcon(const DeviceIcon& icon) noexcept
	{
		return DeviceIcon(detail::Copy(icon.myIcon), icon.myLength);
	}

	bool TryCopyIcon(const DeviceIcon& icon, DeviceIcon& output) noexcept
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

	bool DrawIcon(const DeviceIcon& icon, const ::HDC& hdc, const int& x, const int& y) noexcept
	{
		return detail::Draw(icon.GetHandle(), hdc, x, y);
	}
}

export namespace gl::device
{
	using resource::MakeEmptyIcon;
}
