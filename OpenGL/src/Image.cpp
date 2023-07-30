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

bool
ExtractFile(const std::string_view& filepath, std::vector<std::uint8_t>& output)
{
	util::io::File file{ filepath, util::io::file::OpenModes::Read };
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
