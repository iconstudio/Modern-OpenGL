module;
#include "Internal.hpp"
#include <shellapi.h>

export module Glib.Device.Resource.Icon:Implement;
import <filesystem>;
import <string_view>;

export namespace gl::device
{
	using FilePath = std::filesystem::path;
}

export namespace gl::device::resource::detail
{
	using IconByte = unsigned char;
	using IconBytePtr = IconByte*;

		inline constexpr IconByte SampleZero01x01[] = { 0x00 };
		inline constexpr IconByte SampleFill01x01[] = { 0xFF };
		inline constexpr IconByte SampleZero16x16[] =
		{
			0x00, 0x00, 0x00, 0x00, // 0xF, 0xF, 0xF, 0xF (4 times)
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
		};
		inline constexpr IconByte SampleFill16x16[] =
		{
			0xFF, 0xFF, 0xFF, 0xFF, // 0xF, 0xF, 0xF, 0xF (4 times)
			0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF,
		};

		/// <param name="color">Plain color bitmap</param>
		/// <param name="mask">Should have (1, 2)x resolution of the icon</param>
		[[nodiscard]]
		::ICONINFO ConstructMeta(const ::HBITMAP& color, const ::HBITMAP& mask) noexcept
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
		HICON Construct(::ICONINFO meta) noexcept
		{
			return ::CreateIconIndirect(&meta);
		}

		[[nodiscard]]
		bool TryConstruct(HICON& output, ::ICONINFO meta) noexcept
		{
			return nullptr != (output = ::CreateIconIndirect(&meta));
		}

		[[nodiscard]]
		HICON LoadResource(const std::wstring_view& name) noexcept
		{
			return ::LoadIcon(nullptr, name.data());
		}

		[[nodiscard]]
		bool TryLoadResource(HICON& output, const std::wstring_view& name) noexcept
		{
			return nullptr != (output = LoadResource(name));
		}

		[[nodiscard]]
		HICON LoadResource(const int& id) noexcept
		{
			return ::LoadIcon(nullptr, MAKEINTRESOURCE(id));
		}

		[[nodiscard]]
		bool TryLoadResource(HICON& output, const int& id) noexcept
		{
			return nullptr != (output = LoadResource(id));
		}

		[[nodiscard]]
		HICON Create(const int& width, const int& height
			, const IconBytePtr& and_plain_mask
			, const IconBytePtr& xor_color_mask, const unsigned char& xor_bits_per_pixel, const unsigned char& xor_planes = 1
		) noexcept
		{
			return ::CreateIcon(nullptr, width, height
				, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);
		}

		[[nodiscard]]
		bool TryCreate(HICON& output, const int& width, const int& height
			, const IconBytePtr& and_plain_mask
			, const IconBytePtr& xor_color_mask, const unsigned char& xor_bits_per_pixel, const unsigned char& xor_planes = 1
		) noexcept
		{
			output = ::CreateIcon(nullptr, width, height
				, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);

			return nullptr != output;
		}

		[[nodiscard]]
		HICON ExtractFrom(const FilePath& path, const unsigned int& index) noexcept
		{
			return ::ExtractIcon(nullptr, path.c_str(), index);
		}

		template<unsigned int Count, size_t SmallNumber, size_t LargeNumber>
		[[nodiscard]]
		unsigned int ExtractFrom(const FilePath& path
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
		HICON Copy(const HICON& icon) noexcept
		{
			return ::CopyIcon(icon);
		}

		[[nodiscard]]
		bool TryCopy(const HICON& icon, HICON& output) noexcept
		{
			output = ::CopyIcon(icon);

			return nullptr != output;
		}

		bool Destroy(const HICON& icon) noexcept
		{
			return 0 != ::DestroyIcon(icon);
		}

		bool Draw(const HICON& icon, const ::HDC& hdc, const int& x, const int& y) noexcept
		{
			return 0 != ::DrawIcon(hdc, x, y, icon);
		}

		[[nodiscard]]
		unsigned int GetIconsNumber(const FilePath& path) noexcept
		{
			return ::ExtractIconEx(path.c_str(), -1, nullptr, nullptr, static_cast<unsigned int>(-1));
		}

		[[nodiscard]]
		::ICONINFO GetInfo(const HICON& icon) noexcept
		{
			::ICONINFO result{};

			::GetIconInfo(icon, &result);

			return result;
		}

		[[nodiscard]]
		bool TryGetInfo(const HICON& icon, ::ICONINFO& output) noexcept
		{
			return 0 != ::GetIconInfo(icon, &output);
		}
}
