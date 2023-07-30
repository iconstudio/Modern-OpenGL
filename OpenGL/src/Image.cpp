module;
#include <Windows.h>
#include <gl/GL.h>
#include "../fpng.h"

module Glib.Texture;
import <cstdint>;
import <vector>;
import <string_view>;
import :Image;
import Utility.IO.File;

bool ExtractFile(const std::string_view& filepath, std::vector<std::uint8_t>& output);

class BindedAllocator
{
public:
	using value_type = std::uint8_t;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	constexpr BindedAllocator() noexcept = default;
	constexpr ~BindedAllocator() noexcept = default;

	[[nodiscard]]
	constexpr value_type* allocate(const size_type& count)
	{
		return target = internalAlloc.allocate(count);
	}

	constexpr void deallocate(value_type* const handle, const size_t count)
	{
		if (handle == target)
		{
			target = nullptr;
		}

		internalAlloc.deallocate(handle, count);
	}

	constexpr BindedAllocator(const BindedAllocator&) noexcept = default;
	constexpr BindedAllocator(BindedAllocator&&) noexcept = default;

	std::allocator<value_type> internalAlloc{};
	value_type* target = nullptr;
};

gl::Image::Image(nullptr_t)
noexcept
	: Image()
{
	std::call_once(gl::Image::initFlag, []() noexcept {
		fpng::fpng_init();
	});
}

gl::Image::Image(std::string_view filepath)
{
	std::call_once(gl::Image::initFlag, []() noexcept {
		fpng::fpng_init();
	});

	BindedAllocator myAlloc{};

	std::vector<std::uint8_t, BindedAllocator> buffer{};
	if (!ExtractFile(filepath, buffer))
	{
		return;
	}

	size_t out_hsize = 0;
	size_t out_vsize = 0;
	size_t out_channels = 0;

	int result = fpng::fpng_decode_file(filepath.data(), buffer, out_hsize, out_vsize, out_channels, 4);

	if (fpng::FPNG_DECODE_SUCCESS != result)
	{
		return;
	}
}

bool
ExtractFile(const std::string_view& filepath, std::vector<std::uint8_t>& output)
{
	using namespace util::io;

	File file{ filepath, file::OpenModes::Read | file::OpenModes::Binary };
	if (!file.IsOpen())
	{
		return false;
	}

	if (file.IsEndOfFile())
	{
		return false;
	}

	output.reserve(file.GetSize());

	const size_t count = file.Read(output.data(), output.size());
	if (count < output.size())
	{
		return false;
	}

	return true;
}

std::once_flag gl::Image::initFlag{};
