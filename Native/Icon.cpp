module;
#include "Internal.hpp"
#include <shellapi.h>
module Glib.Device.Resource.Icon;

gl::device::resource::Icon&
gl::device::resource::Icon::operator=(nullptr_t)
noexcept
{
	Destroy();
	myLength = 0U;

	return *this;
}

gl::device::resource::Icon::~Icon()
noexcept
{
	Destroy();
	myLength = 0U;
}

gl::device::resource::Icon
gl::device::resource::Icon::Copy()
const noexcept
{
	gl::device::resource::Icon result{ nullptr };

	native::RawIcon copy = ::CopyIcon(GetHandle());
	if (nullptr != copy)
	{
		result.myLength = myLength;
		return result;
	}

	return nullptr;
}

bool
gl::device::resource::Icon::TryCopy(Icon& output)
const noexcept
{
	native::RawIcon copy = ::CopyIcon(GetHandle());
	if (nullptr != copy)
	{
		output.myLength = myLength;
		return true;
	}

	return false;
}

bool
gl::device::resource::Icon::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		return 0 != Delegate(::DestroyIcon);
	}
	else
	{
		return false;
	}
}

bool
gl::device::resource::Icon::Draw(const gl::device::native::NativeContext& hdc, const int& x, const int& y)
const noexcept
{
	return 0 != ::DrawIcon(hdc, x, y, GetHandle());
}

gl::device::resource::Icon
gl::device::MakeEmptyIcon() noexcept
{
	return resource::Icon(nullptr);
}

namespace gl::device::resource
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

	[[nodiscard]]
	native::RawIcon Construct(::ICONINFO meta) noexcept
	{
		return ::CreateIconIndirect(&meta);
	}

	[[nodiscard]]
	bool TryConstruct(native::RawIcon& output, ::ICONINFO meta) noexcept
	{
		return nullptr != (output = ::CreateIconIndirect(&meta));
	}

	[[nodiscard]]
	native::RawIcon LoadResource(const std::wstring_view& name) noexcept
	{
		return ::LoadIcon(nullptr, name.data());
	}

	[[nodiscard]]
	bool TryLoadResource(native::RawIcon& output, const std::wstring_view& name) noexcept
	{
		return nullptr != (output = LoadResource(name));
	}

	[[nodiscard]]
	native::RawIcon LoadResource(const int& id) noexcept
	{
		return ::LoadIconW(nullptr, MAKEINTRESOURCE(id));
	}

	[[nodiscard]]
	bool TryLoadResource(native::RawIcon& output, const int& id) noexcept
	{
		return nullptr != (output = LoadResource(id));
	}

	[[nodiscard]]
	native::RawIcon Create(const int& width, const int& height
		, const IconBytePtr& and_plain_mask
		, const IconBytePtr& xor_color_mask, const unsigned char& xor_bits_per_pixel, const unsigned char& xor_planes = 1
	) noexcept
	{
		return ::CreateIcon(nullptr, width, height
			, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);
	}

	[[nodiscard]]
	bool TryCreate(native::RawIcon& output, const int& width, const int& height
		, const IconBytePtr& and_plain_mask
		, const IconBytePtr& xor_color_mask, const unsigned char& xor_bits_per_pixel, const unsigned char& xor_planes = 1
	) noexcept
	{
		output = ::CreateIcon(nullptr, width, height
			, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);

		return nullptr != output;
	}

	[[nodiscard]]
	native::RawIcon ExtractFrom(const FilePath& path, const unsigned int& index) noexcept
	{
		return ::ExtractIcon(nullptr, path.c_str(), index);
	}

	template<unsigned int Count, size_t SmallNumber, size_t LargeNumber>
	[[nodiscard]]
	unsigned int ExtractFrom(const FilePath& path
		, const int& index
		, _Notnull_ native::RawIcon(&smalls)[SmallNumber]
		, _Notnull_ native::RawIcon(&larges)[LargeNumber]
	) noexcept
	{
		static_assert(0 < SmallNumber);
		static_assert(0 < LargeNumber);
		static_assert(0 < Count);
		static_assert(SmallNumber <= SmallNumber);
		static_assert(Count <= LargeNumber);

		return ::ExtractIconEx(path.c_str(), (index), larges, smalls, Count);
	}

	[[nodiscard]]
	unsigned int GetIconsNumber(const FilePath& path) noexcept
	{
		return ::ExtractIconEx(path.c_str(), -1, nullptr, nullptr, static_cast<unsigned int>(-1));
	}

#undef LoadIcon
	Icon LoadIcon(const FilePath& path) noexcept
	{
		return Icon(ExtractFrom(path, 0), GetIconsNumber(path));
	}

	bool TryLoadIcon(const FilePath& path, Icon& output) noexcept
	{
		if (nullptr != ExtractFrom(path, 0))
		{
			output.myLength = GetIconsNumber(path);
			return true;
		}
		else
		{
			return false;
		}
	}

	Icon LoadIconAt(const FilePath& path, const unsigned int& index) noexcept
	{
		return Icon(ExtractFrom(path, index), GetIconsNumber(path));
	}

	bool TryLoadIconAt(const FilePath& path, const unsigned int& index, Icon& output) noexcept
	{
		if (nullptr != ExtractFrom(path, index))
		{
			output.myLength = GetIconsNumber(path);
			return true;
		}
		else
		{
			return false;
		}
	}

	Icon LoadIcon(const int& id) noexcept
	{
		return Icon(LoadResource(id), 1);
	}

	bool TryLoadIcon(const int& id, Icon& output) noexcept
	{
		if (TryLoadResource(output.GetHandle(), id))
		{
			output.myLength = 1;
			return true;
		}
		else
		{
			return false;
		}
	}
}

namespace gl::device::resource::detail
{
	using device::native::RawIcon;

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
	::ICONINFO GetInfo(const RawIcon& icon) noexcept
	{
		::ICONINFO result{};

		::GetIconInfo(icon, &result);

		return result;
	}

	[[nodiscard]]
	bool TryGetInfo(const RawIcon& icon, ::ICONINFO& output) noexcept
	{
		return 0 != ::GetIconInfo(icon, &output);
	}
}
