export module Glib.Window.Property.Factory;
import <type_traits>;
import Utility.FixedString;
import Glib.Device.ProcessInstance;
import Glib.Device.Resource.Brush;
import Glib.Device.Resource.Brush.Component;
import Glib.Device.Resource.Icon;
export import Glib.Window.Property;

export namespace gl::win32
{
	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const resource::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = DefaultWindowProperty.cbClsExtra,
				.cbWndExtra = DefaultWindowProperty.cbWndExtra,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = background.GetHandle(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const resource::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return CreateProperty(GetProcessInstance(), procedure, class_name
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, background, menu_name);
	}

	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, resource::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = DefaultWindowProperty.cbClsExtra,
				.cbWndExtra = DefaultWindowProperty.cbWndExtra,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = std::move(background).GetHandle(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, resource::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return CreateProperty(GetProcessInstance(), procedure, class_name
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, std::move(background), menu_name);
	}

	template<ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = DefaultWindowProperty.cbClsExtra,
				.cbWndExtra = DefaultWindowProperty.cbWndExtra,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = GetComponentColouring<BkColorReference>(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	template<ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return CreateProperty<BkColorReference>(GetProcessInstance(), procedure, class_name
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, menu_name);
	}

	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon = nullptr
		, resource::Icon&& small_icon = nullptr
		, resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = DefaultWindowProperty.cbClsExtra,
				.cbWndExtra = DefaultWindowProperty.cbWndExtra,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = MakeDefaultComponentColouring(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, const wchar_t* const& class_name
		, resource::Icon&& icon = nullptr
		, resource::Icon&& small_icon = nullptr
		, resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return CreateProperty(GetProcessInstance(), procedure, class_name
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const resource::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), background, menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const resource::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(GetProcessInstance(), procedure, ClassName.data()
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, background, menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, resource::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), std::move(background), menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, resource::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(GetProcessInstance(), procedure, ClassName.data()
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, std::move(background), menu_name);
	}

	template<util::fixed_wstring ClassName, ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty<BkColorReference>(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), menu_name);
	}

	template<util::fixed_wstring ClassName, ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, resource::Icon&& icon
		, resource::Icon&& small_icon
		, resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty<BkColorReference>(GetProcessInstance(), procedure, ClassName.data()
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(const ProcessInstance& hinst
		, WindowProcedure procedure
		, resource::Icon&& icon = nullptr
		, resource::Icon&& small_icon = nullptr
		, resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(WindowProcedure procedure
		, resource::Icon&& icon = nullptr
		, resource::Icon&& small_icon = nullptr
		, resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(GetProcessInstance(), procedure, ClassName.data()
			, std::move(icon), std::move(small_icon)
			, std::move(cursor)
			, menu_name);
	}
}
