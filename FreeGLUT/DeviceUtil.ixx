module;
#include "Internal.hpp"

export module Glib.Device.Utility;
export import <utility>;

export namespace gl::device
{
#undef MAKEWORD
[[nodiscard]]
	constexpr unsigned short MAKEWORD(const std::integral auto& a, const std::integral auto& b) noexcept
	{
		return static_cast<unsigned short>((static_cast<unsigned long long>(a) & 0xFF) | ((static_cast<unsigned long long>(b) & 0xFF) << 8));
	}

#undef MAKELONG
[[nodiscard]]
	constexpr unsigned int MAKELONG(const std::integral auto& a, const std::integral auto& b) noexcept
	{
		return static_cast<unsigned int>((static_cast<unsigned long long>(a) & 0xFFFF) | ((static_cast<unsigned long long>(b) & 0xFFFF) << 16));
	}

#undef LOWORD
[[nodiscard]]
	constexpr unsigned short LOWORD(const std::integral auto& value) noexcept
	{
		return static_cast<unsigned short>(static_cast<unsigned long long>(value) & 0xFFFF);
	}

#undef HIWORD
[[nodiscard]]
	constexpr unsigned short HIWORD(const std::integral auto& value) noexcept
	{
		return static_cast<unsigned short>((static_cast<unsigned long long>(value) >> 16) & 0xFFFF);
	}

#undef LOBYTE
	[[nodiscard]]
	constexpr unsigned char LOBYTE(const std::integral auto& value) noexcept
	{
		return static_cast<unsigned char>(static_cast<unsigned long long>(value) & 0xFF);
	}

#undef HIBYTE
	[[nodiscard]]
	constexpr unsigned char HIBYTE(const std::integral auto& value) noexcept
	{
		return static_cast<unsigned char>((static_cast<unsigned long long>(value) >> 8)) & 0xFF;
	}
}
