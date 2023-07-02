export module Glib.Window.Factory;
import <type_traits>;
import <string_view>;
import <memory>;
import Utility.FixedString;
export import Glib.Window;
export import Glib.Window.Property.Factory;
export import Glib.Window.ManagedWindow;

export namespace gl::window
{
#pragma region CreateWindow
	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ properties, title, style, option, x, y, width, height };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, option, x, y, width, height };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const Rect& dimension) noexcept
	{
		return Window{ properties, title, style, option, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const WindowStyle& style, const WindowOption& option, const Rect& dimension) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, option, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return Window{ properties, title, style, options::Default, x, y, width, height };
	}

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const int& x
		, const int& y
		, const int& width
		, const int& height
	) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, options::Default, x, y, width, height };
	}

	Window CreateWindow(const WindowProperty& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept
	{
		return Window{ properties, title, style, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(WindowProperty&& properties
		, const std::wstring_view& title
		, const WindowStyle& style
		, const Rect& dimension
	) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, style, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ properties, title, styles::Default, options::Default, x, y, width, height };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const int& x, const int& y, const int& width, const int& height) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, styles::Default, options::Default, x, y, width, height };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, const Rect& dimension) noexcept
	{
		return Window{ properties, title, styles::Default, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, const Rect& dimension) noexcept
	{
		return Window{ static_cast<WindowProperty&&>(properties), title, styles::Default, options::Default, dimension.x, dimension.y, dimension.w, dimension.h };
	}

	Window CreateWindow(const WindowProperty& properties, const std::wstring_view& title, Rect&& dimension) noexcept
	{
		return Window
		{
			properties
			, title
			, styles::Default , options::Default
			, std::move(dimension.x), std::move(dimension.y)
			, std::move(dimension.w), std::move(dimension.h)
		};
	}

	Window CreateWindow(WindowProperty&& properties, const std::wstring_view& title, Rect&& dimension) noexcept
	{
		return Window
		{
			std::move(properties)
			, title
			, styles::Default , options::Default
			, std::move(dimension.x), std::move(dimension.y)
			, std::move(dimension.w), std::move(dimension.h)
		};
	}
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
		WindowProperty property = gl::window::CreateProperty(ManagedWindow::MainWorker, class_name_view.data());

		if (!property.Register())
		{
			throw std::runtime_error{ "Failed to register window class" };
		}

		return std::make_unique<gl::window::ManagedWindow>
		(
			gl::window::CreateWindow(property
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
		WindowProperty property = gl::window::CreateProperty(ManagedWindow::MainWorker, class_name_view.data());

		if (!property.Register())
		{
			throw std::runtime_error{ "Failed to register window class" };
		}

		return std::make_unique<gl::window::ManagedWindow>
		(
			gl::window::CreateWindow(property
			, title
			, style
			, option
			, dimension.x, dimension.y, dimension.w, dimension.h)
			, number_of_workers
		);
	}
#pragma endregion
}
