export module Glib.Windows.Client.Factory;
import <string_view>;
import <memory>;
import Utility.FixedString;
import Glib.Rect;
import Glib.Windows.Client;
import Glib.Windows.Client.Property.Factory;
import Glib.Windows.ManagedClient;

export namespace gl::win32
{
#pragma region CreateWindow
	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const int& x, const int& y, const int& width, const int& height
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const int& x, const int& y, const int& width, const int& height
	) noexcept;

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const Rect& dimension
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const WindowOption& option
		, const Rect& dimension
	) noexcept;

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept;

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept;

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const int& x, const int& y, const int& width, const int& height
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const int& x, const int& y, const int& width, const int& height
	) noexcept;

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const Rect& dimension
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const Rect& dimension
	) noexcept;

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, Rect&& dimension
	) noexcept;

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, Rect&& dimension
	) noexcept;
#pragma endregion

#pragma region CreateWindowEx
	template<util::basic_fixed_string NID>
	[[nodiscard]]
	std::unique_ptr<ManagedWindow> CreateWindowEx(const std::wstring_view& title
		, const int& x
		, const int& y
		, const int& width
		, const int& height
		, const int& number_of_workers = 4
		, const WindowStyle& style = styles::Default
		, const WindowOption& option = options::Default
	)
	{
		constexpr std::wstring_view class_name_view{ NID };
		WindowProperty property = CreateProperty(ManagedWindow::MainWorker, class_name_view.data());

		if (!property.Register())
		{
			throw std::runtime_error{ "Failed to register window class" };
		}

		return std::make_unique<ManagedWindow>
			(
				CreateWindow(property
			, title
			, style
			, option
			, x, y, width, height)
				, number_of_workers
			);
	}

	template<util::basic_fixed_string NID>
	[[nodiscard]]
	std::unique_ptr<ManagedWindow> CreateWindowEx(const std::wstring_view& title
		, const Rect& dimension
		, const int& number_of_workers = 4
		, const WindowStyle& style = styles::Default
		, const WindowOption& option = options::Default
	)
	{
		constexpr std::wstring_view class_name_view{ NID };
		WindowProperty property = CreateProperty(ManagedWindow::MainWorker, class_name_view.data());

		if (!property.Register())
		{
			throw std::runtime_error{ "Failed to register window class" };
		}

		return std::make_unique<ManagedWindow>
			(
				CreateWindow(property
			, title
			, style
			, option
			, dimension.x, dimension.y, dimension.w, dimension.h)
				, number_of_workers
			);
	}
#pragma endregion
}
