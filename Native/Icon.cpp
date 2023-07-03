module;
#include "Internal.hpp"
#include <shellapi.h>

module Glib.Device.Resource.Icon;
import Glib.Device.Definitions;

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
	return CopyIcon(*this);
}

bool
gl::device::resource::Icon::TryCopy(Icon& output)
const noexcept
{
	return TryCopyIcon(*this, output);
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
gl::device::resource::Icon::Draw(const gl::device::native::NativeSurface& hdc, const int& x, const int& y)
const noexcept
{
	return DrawIcon(*this, hdc, x, y);
}

gl::device::resource::Icon
gl::device::MakeEmptyIcon() noexcept
{
	return resource::Icon(nullptr);
}

namespace gl::device::resource
{
#undef LoadIcon
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
		if (detail::TryLoadResource(output.GetHandle(), name))
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
		if (detail::TryLoadResource(output.GetHandle(), id))
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
		return Icon(detail::Copy(icon.GetHandle()), icon.myLength);
	}

	bool TryCopyIcon(const Icon& icon, Icon& output) noexcept
	{
		if (detail::TryCopy(icon.GetHandle(), output.GetHandle()))
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

	bool DestroyIcon(Icon& icon) noexcept
	{
		return detail::Destroy(icon.GetHandle());
	}
}

namespace gl::device::resource::detail
{
	using device::native::RawIcon;
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
	RawIcon Construct(::ICONINFO meta) noexcept
	{
		return ::CreateIconIndirect(&meta);
	}

	[[nodiscard]]
	bool TryConstruct(RawIcon& output, ::ICONINFO meta) noexcept
	{
		return nullptr != (output = ::CreateIconIndirect(&meta));
	}

	[[nodiscard]]
	RawIcon LoadResource(const std::wstring_view& name) noexcept
	{
		return ::LoadIcon(nullptr, name.data());
	}

	[[nodiscard]]
	bool TryLoadResource(RawIcon& output, const std::wstring_view& name) noexcept
	{
		return nullptr != (output = LoadResource(name));
	}

	[[nodiscard]]
	RawIcon LoadResource(const int& id) noexcept
	{
		return ::LoadIconW(nullptr, MAKEINTRESOURCE(id));
	}

	[[nodiscard]]
	bool TryLoadResource(RawIcon& output, const int& id) noexcept
	{
		return nullptr != (output = LoadResource(id));
	}

	[[nodiscard]]
	RawIcon Create(const int& width, const int& height
		, const IconBytePtr& and_plain_mask
		, const IconBytePtr& xor_color_mask, const unsigned char& xor_bits_per_pixel, const unsigned char& xor_planes = 1
	) noexcept
	{
		return ::CreateIcon(nullptr, width, height
			, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);
	}

	[[nodiscard]]
	bool TryCreate(RawIcon& output, const int& width, const int& height
		, const IconBytePtr& and_plain_mask
		, const IconBytePtr& xor_color_mask, const unsigned char& xor_bits_per_pixel, const unsigned char& xor_planes = 1
	) noexcept
	{
		output = ::CreateIcon(nullptr, width, height
			, xor_planes, xor_bits_per_pixel, and_plain_mask, xor_color_mask);

		return nullptr != output;
	}

	[[nodiscard]]
	RawIcon ExtractFrom(const FilePath& path, const unsigned int& index) noexcept
	{
		return ::ExtractIcon(nullptr, path.c_str(), index);
	}

	template<unsigned int Count, size_t SmallNumber, size_t LargeNumber>
	[[nodiscard]]
	unsigned int ExtractFrom(const FilePath& path
		, const int& index
		, _Notnull_ RawIcon(&smalls)[SmallNumber]
		, _Notnull_ RawIcon(&larges)[LargeNumber]
	) noexcept(Count < SmallNumber&& Count < LargeNumber)
	{
		static_assert(0 < SmallNumber);
		static_assert(0 < LargeNumber);
		static_assert(0 < Count);

		return ::ExtractIconEx(path.c_str(), ::abs(index), larges, smalls, Count);
	}

	[[nodiscard]]
	RawIcon Copy(const RawIcon& icon) noexcept
	{
		return ::CopyIcon(icon);
	}

	[[nodiscard]]
	bool TryCopy(const RawIcon& icon, RawIcon& output) noexcept
	{
		output = ::CopyIcon(icon);

		return nullptr != output;
	}

	bool Draw(const RawIcon& icon, const ::HDC& hdc, const int& x, const int& y) noexcept
	{
		return 0 != ::DrawIcon(hdc, x, y, icon);
	}

	[[nodiscard]]
	unsigned int GetIconsNumber(const FilePath& path) noexcept
	{
		return ::ExtractIconEx(path.c_str(), -1, nullptr, nullptr, static_cast<unsigned int>(-1));
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

	bool Destroy(RawIcon& icon) noexcept
	{
		return 0 != ::DestroyIcon(icon);
	}
}
