module;
#include "Internal.hpp"
#include <shellapi.h>

export module Glib.Device.Icon;
export import <filesystem>;

export namespace gl::device
{
	using FilePath = std::filesystem::path;

	class IconAPI
	{
	public:
		[[nodiscard]]
		static HICON Load(const FilePath& path) noexcept
		{
			return ::LoadIcon(nullptr, path.c_str());
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
