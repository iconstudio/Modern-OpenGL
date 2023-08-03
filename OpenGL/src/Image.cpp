module;
#include <Windows.h>
#include <gl/GL.h>
#include <atlimage.h>
#include "../fpng.h"

module Glib.Image;
import <cstdint>;
import <vector>;
import <string_view>;

bool ExtractFile(const std::string_view& filepath, std::vector<std::uint8_t>& output);

namespace gl
{
	class Image;
}

gl::Image::Image(nullptr_t)
noexcept
	: Image()
{
	std::call_once(gl::Image::initFlag, []() noexcept {
		fpng::fpng_init();
	});
}

gl::Image::Image(const std::filesystem::path& filepath)
{
	std::call_once(gl::Image::initFlag, []() noexcept {
		fpng::fpng_init();
	});

	std::vector<std::uint8_t> buffer{};
	if (!ExtractFile(filepath.string().c_str(), buffer))
	{
		return;
	}

	size_t out_hsize = 0;
	size_t out_vsize = 0;
	size_t out_channels = 0;

	int result = fpng::fpng_decode_file(filepath.string().c_str()
		, buffer
		, out_hsize, out_vsize, out_channels
		, 4);

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
