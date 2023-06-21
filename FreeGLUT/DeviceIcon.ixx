module;
#include "Internal.hpp"
#include <shellapi.h>

export module Glib.Device.Icon;
export import <string_view>;
export import <filesystem>;

export namespace gl::device
{
	using FilePath = std::filesystem::path;
	using IconByte = unsigned char;
	using IconBytePtr = IconByte*;

	class IconAPI
	{
	public:
		static constexpr IconByte SampleZero01x01[] = { 0x00 };
		static constexpr IconByte SampleFill01x01[] = { 0xFF };
		static constexpr IconByte SampleZero16x16[] =
		{
			0x00, 0x00, 0x00, 0x00, // 0xF, 0xF, 0xF, 0xF (4 times)
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
		};
		static constexpr IconByte SampleFill16x16[] =
		{
			0xFF, 0xFF, 0xFF, 0xFF, // 0xF, 0xF, 0xF, 0xF (4 times)
			0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF,
		};

		/// <param name="color">Plain color bitmap</param>
		/// <param name="mask">Should have (1, 2)x resolution of the icon</param>
		[[nodiscard]]
		static ::ICONINFO ConstructMeta(const ::HBITMAP& color, const ::HBITMAP& mask) noexcept
		{
			return ::ICONINFO
			{
				TRUE // is icon?
					, 0 // x hotspot for cursor
					, 0 // y hotspot for cursor
					, mask // hbmMask
					, color // hbmColor
			};
		}

		[[nodiscard]]
		static HICON Construct(::ICONINFO meta) noexcept
		{
			return ::CreateIconIndirect(&meta);
		}

		[[nodiscard]]
		static bool TryConstruct(HICON& output, ::ICONINFO meta) noexcept
		{
			return nullptr != (output = ::CreateIconIndirect(&meta));
		}

		[[nodiscard]]
		static HICON LoadResource(const std::wstring_view& name) noexcept
		{
			return ::LoadIcon(nullptr, name.data());
		}

		[[nodiscard]]
		static bool TryLoadResource(HICON& output, const std::wstring_view& name) noexcept
		{
			return nullptr != (output = LoadResource(name));
		}

		[[nodiscard]]
		static HICON LoadResource(const int& id) noexcept
		{
			return ::LoadIcon(nullptr, MAKEINTRESOURCE(id));
		}

		[[nodiscard]]
		static bool TryLoadResource(HICON& output, const int& id) noexcept
		{
			return nullptr != (output = LoadResource(id));
		}

		[[nodiscard]]
		static HICON Create(const int& width, const int& height
			, const IconBytePtr& and_plain_mask
			, const IconBytePtr& xor_color_mask, const unsigned int& xor_bits_per_pixel, const unsigned int& xor_planes = 1
		) noexcept
		{
			return ::CreateIcon(nullptr, width, height
				, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);
		}

		[[nodiscard]]
		static bool TryCreate(HICON& output, const int& width, const int& height
			, const IconBytePtr& and_plain_mask
			, const IconBytePtr& xor_color_mask, const unsigned int& xor_bits_per_pixel, const unsigned int& xor_planes = 1
		) noexcept
		{
			output = ::CreateIcon(nullptr, width, height
				, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);

			return nullptr != output;
		}

		[[nodiscard]]
		static HICON ExtractFrom(const FilePath& path, const unsigned int& index) noexcept
		{
			return ::ExtractIcon(nullptr, path.c_str(), index);
		}

		template<unsigned int Count, size_t SmallNumber, size_t LargeNumber>
		[[nodiscard]]
		static unsigned int ExtractFrom(const FilePath& path
			, const int& index
			, _Notnull_ HICON(&smalls)[SmallNumber]
			, _Notnull_ HICON(&larges)[LargeNumber]
		) noexcept(Count < SmallNumber&& Count < LargeNumber)
		{
			static_assert(0 < SmallNumber);
			static_assert(0 < LargeNumber);
			static_assert(0 < Count);

			return ::ExtractIconEx(path.c_str(), ::abs(index), larges, smalls, Count);
		}

		[[nodiscard]]
		static HICON Copy(const HICON& icon) noexcept
		{
			return ::CopyIcon(icon);
		}

		[[nodiscard]]
		static bool TryCopy(const HICON& icon, HICON& output) noexcept
		{
			output = ::CopyIcon(icon);

			return nullptr != output;
		}

		static bool Destroy(const HICON& icon) noexcept
		{
			return 0 != ::DestroyIcon(icon);
		}

		static bool Draw(const HICON& icon, const ::HDC& hdc, const int& x, const int& y) noexcept
		{
			return 0 != ::DrawIcon(hdc, x, y, icon);
		}

		[[nodiscard]]
		static unsigned int GetIconsNumber(const FilePath& path) noexcept
		{
			return ::ExtractIconEx(path.c_str(), -1, nullptr, nullptr, -1);
		}

		[[nodiscard]]
		static ::ICONINFO GetInfo(const HICON& icon) noexcept
		{
			::ICONINFO result{};

			::GetIconInfo(icon, &result);

			return result;
		}

		[[nodiscard]]
		static bool TryGetInfo(const HICON& icon, ::ICONINFO& output) noexcept
		{
			return 0 != ::GetIconInfo(icon, &output);
		}
	};

#undef LoadIcon
#undef DrawIcon

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
				IconAPI::Destroy(myIcon);
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
		return DeviceIcon(IconAPI::ExtractFrom(path, 0), IconAPI::GetIconsNumber(path));
	}

	bool TryLoadIcon(const FilePath& path, DeviceIcon& output) noexcept
	{
		if (nullptr != IconAPI::ExtractFrom(path, 0))
		{
			output.myLength = IconAPI::GetIconsNumber(path);
			return true;
		}
		else
		{
			return false;
		}
	}

	DeviceIcon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept
	{
		return DeviceIcon(IconAPI::ExtractFrom(path, index), IconAPI::GetIconsNumber(path));
	}

	bool TryLoadIconAt(const FilePath& path, const unsigned int& index, DeviceIcon& output) noexcept
	{
		if (nullptr != IconAPI::ExtractFrom(path, index))
		{
			output.myLength = IconAPI::GetIconsNumber(path);
			return true;
		}
		else
		{
			return false;
		}
	}

	DeviceIcon LoadResource(const std::wstring_view& name) noexcept
	{
		return DeviceIcon(IconAPI::LoadResource(name), 1);
	}

	bool TryLoadResource(const std::wstring_view& name, DeviceIcon& output) noexcept
	{
		if (IconAPI::TryLoadResource(output.myIcon, name))
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
		return DeviceIcon(IconAPI::LoadResource(id), 1);
	}

	bool TryLoadResource(const int& id, DeviceIcon& output) noexcept
	{
		if (IconAPI::TryLoadResource(output.myIcon, id))
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
		return DeviceIcon(IconAPI::Copy(icon.myIcon), icon.myLength);
	}

	bool TryCopyIcon(const DeviceIcon& icon, DeviceIcon& output) noexcept
	{
		if (IconAPI::TryCopy(icon.myIcon, output.myIcon))
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
		return IconAPI::Draw(icon, hdc, x, y);
	}
}
