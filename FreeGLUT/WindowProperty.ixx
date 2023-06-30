module;
#include "Internal.hpp"

export module Glib.Window:Property;
import <type_traits>;
import Glib.Device.ProcessInstance;
export import Glib.Device.Brush;
export import Glib.Device.Icon;

export extern "C++" namespace gl::window
{
	//using ::WNDPROC;
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);

	class [[nodiscard]] WindowProperty
	{
	protected:
		template<typename IconType, typename CursorType>
		explicit constexpr WindowProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name
		) noexcept
			: myWindowClass()
		{
			myWindowClass.cbSize = sizeof(RawWindowProperty);
			myWindowClass.hInstance = hinst.myHandle;
			myWindowClass.lpszClassName = class_name;
			myWindowClass.lpfnWndProc = procedure;
			myWindowClass.cbClsExtra = 0;
			myWindowClass.cbWndExtra = 0;
			myWindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			myWindowClass.hbrBackground = background;
			myWindowClass.lpszMenuName = menu_name;
			myWindowClass.hIcon = static_cast<IconType&&>(icon).GetHandle();
			myWindowClass.hIconSm = static_cast<IconType&&>(small_icon).GetHandle();
			myWindowClass.hCursor = static_cast<CursorType&&>(cursor);
		}

	public:
		using RawWindowProperty = ::tagWNDCLASSEXW;

		constexpr WindowProperty() noexcept = default;
		constexpr ~WindowProperty() noexcept = default;

		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst, WindowProcedure procedure, const wchar_t* const& class_name) noexcept;

		template<typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, const device::ColorBrush& background
			, const wchar_t* const& menu_name) noexcept;

		template<typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, device::ColorBrush&& background
			, const wchar_t* const& menu_name) noexcept;

		template<typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, const device::NativeColorBrush& background
			, const wchar_t* const& menu_name) noexcept;

		template<typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, device::NativeColorBrush&& background
			, const wchar_t* const& menu_name) noexcept;

		template<device::ColoredComponent BkColorReference, typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, const wchar_t* const& menu_name) noexcept;

		template<typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst
			, WindowProcedure procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, const wchar_t* const& menu_name) noexcept;

		inline bool Register() noexcept
		{
			return 0 == ::RegisterClassEx(std::addressof(myWindowClass));
		}

		inline bool Deregister() noexcept
		{
			return FALSE != ::UnregisterClass(myWindowClass.lpszClassName, myWindowClass.hInstance);
		}

		[[nodiscard]]
		constexpr const RawWindowProperty& GetHandle() const& noexcept
		{
			return myWindowClass;
		}

		[[nodiscard]]
		constexpr RawWindowProperty&& GetHandle() && noexcept
		{
			return static_cast<RawWindowProperty&&>(myWindowClass);
		}

		[[nodiscard]]
		constexpr device::ProcessInstance GetInstance() const& noexcept
		{
			return device::ProcessInstance{ myWindowClass.hInstance };
		}

		[[nodiscard]]
		constexpr device::ProcessInstance GetInstance() && noexcept
		{
			return device::ProcessInstance{ static_cast<device::HINSTANCE&&>(myWindowClass.hInstance) };
		}

		[[nodiscard]]
		constexpr const WindowProcedure& GetProcedure() const& noexcept
		{
			return myWindowClass.lpfnWndProc;
		}

		[[nodiscard]]
		constexpr WindowProcedure&& GetProcedure() && noexcept
		{
			return static_cast<WindowProcedure&&>(myWindowClass.lpfnWndProc);
		}

		[[nodiscard]]
		constexpr const wchar_t* const& GetClass() const& noexcept
		{
			return myWindowClass.lpszClassName;
		}

		[[nodiscard]]
		constexpr const wchar_t*&& GetClass() && noexcept
		{
			return static_cast<const wchar_t*&&>(myWindowClass.lpszClassName);
		}

		constexpr WindowProperty(const WindowProperty&) noexcept = default;
		constexpr WindowProperty& operator=(const WindowProperty&) noexcept = default;
		constexpr WindowProperty(WindowProperty&&) noexcept = default;
		constexpr WindowProperty& operator=(WindowProperty&&) noexcept = default;

	private:
		RawWindowProperty myWindowClass{};
	};

	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure, const wchar_t* const& class_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, device::MakeEmptyIcon() //, LoadIconW(hinst, IDI_APPLICATION)
			, device::MakeEmptyIcon() //, LoadIconW(hinst, IDI_APPLICATION)
			, nullptr //, LoadCursorW(hinst, IDC_ARROW)
			, device::MakeDefaultComponentColouring()
			, nullptr
		};
	}

	template<typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, const device::ColorBrush& background
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, std::forward<IconType>(icon)
			, std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, background.GetHandle()
			, menu_name
		};
	}

	template<typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, device::ColorBrush&& background
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, std::forward<IconType>(icon)
			, std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, std::move(background).GetHandle()
			, menu_name
		};
	}

	template<typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, const device::NativeColorBrush& background
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, std::forward<IconType>(icon)
			, std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, background
			, menu_name
		};
	}

	template<typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, device::NativeColorBrush&& background
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, std::forward<IconType>(icon)
			, std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, std::move(background)
			, menu_name
		};
	}

	template<device::ColoredComponent BkColorReference, typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, std::forward<IconType>(icon)
			, std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, device::GetComponentColouring<BkColorReference>()
			, menu_name
		};
	}

	template<typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, std::forward<IconType>(icon)
			, std::forward<IconType>(small_icon)
			, std::forward<CursorType>(cursor)
			, device::MakeDefaultComponentColouring()
			, menu_name
		};
	}
}
