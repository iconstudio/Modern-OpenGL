module;
#include "Internal.hpp"
#include <shellapi.h>

export module Glib.Device.Icon;
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

		[[nodiscard]]
		static HICON Load(const FilePath& path) noexcept
		{
			return ::LoadIcon(nullptr, path.c_str());
		}

		[[nodiscard]]
		static HICON LoadResource(const int& id) noexcept
		{
			return ::LoadIcon(nullptr, MAKEINTRESOURCE(id));
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

	class [[nodiscard]] DeviceIcon
	{
	protected:

	public:

	private:
		HICON myIcon;
	};
}
