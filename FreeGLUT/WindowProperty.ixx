module;
#include "Internal.hpp"

export module Glib.Window:Property;
import Glib.Device.ProcessInstance;
export import Glib.Device.Icon;
import :ABI;

export namespace gl::window
{
	class [[nodiscard]] WindowProperty
	{
	protected:
		template<typename IconType, typename CursorType>
		explicit constexpr WindowProperty(const device::ProcessInstance& hinst
			, ::WNDPROC procedure
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
			myWindowClass.hInstance = hinst;
			myWindowClass.lpszClassName = class_name;
			myWindowClass.lpfnWndProc = procedure;
			myWindowClass.cbClsExtra = 0;
			myWindowClass.cbWndExtra = 0;
			myWindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			myWindowClass.hbrBackground = background;
			myWindowClass.lpszMenuName = menu_name;
			myWindowClass.hIcon = static_cast<IconType&&>(icon).GetHandle();
			myWindowClass.hIconSm = static_cast<IconType&&>(small_icon).GetHandle();
			myWindowClass.hCursor = cursor;
		}

	public:
		using RawWindowProperty = ::tagWNDCLASSEXW;

		constexpr WindowProperty() noexcept = default;
		constexpr ~WindowProperty() noexcept = default;

		template<size_t ClassNameSize>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst, WNDPROC procedure, const wchar_t(&class_name)[ClassNameSize]
		) noexcept;

		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst, WNDPROC procedure, const wchar_t* const& class_name
		) noexcept;

		template<typename IconType, typename CursorType>
		[[nodiscard]]
		friend WindowProperty CreateProperty(const device::ProcessInstance& hinst, WNDPROC procedure
			, const wchar_t* const& class_name
			, IconType&& icon
			, IconType&& small_icon
			, CursorType&& cursor
			, const ::HBRUSH& background
			, const wchar_t* const& menu_name
		) noexcept;

		inline bool Register() noexcept
		{
			return detail::RegisterProcess(myWindowClass);
		}

		inline bool Deregister() noexcept
		{
			return detail::UnregisterProcess(myWindowClass.hInstance, myWindowClass.lpszClassName);
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
		constexpr const device::ProcessInstance& GetInstance() const& noexcept
		{
			return myWindowClass.hInstance;
		}

		[[nodiscard]]
		constexpr device::ProcessInstance&& GetInstance() && noexcept
		{
			return static_cast<device::ProcessInstance&&>(myWindowClass.hInstance);
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
		RawWindowProperty myWindowClass;
	};

	WindowProperty CreateProperty(const device::ProcessInstance& hinst, WNDPROC procedure, const wchar_t* const& class_name
	) noexcept
	{
		static const HBRUSH default_color = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, device::MakeEmptyIcon() //, LoadIconW(hinst, IDI_APPLICATION)
			, device::MakeEmptyIcon() //, LoadIconW(hinst, IDI_APPLICATION)
			, nullptr //, LoadCursorW(hinst, IDC_ARROW)
			, default_color
			, nullptr
		};
	}

	template<typename IconType, typename CursorType>
	WindowProperty CreateProperty(const device::ProcessInstance& hinst, WNDPROC procedure
		, const wchar_t* const& class_name
		, IconType&& icon
		, IconType&& small_icon
		, CursorType&& cursor
		, const ::HBRUSH& background
		, const wchar_t* const& menu_name
	) noexcept
	{
		return WindowProperty
		{
			hinst
			, procedure
			, class_name
			, static_cast<IconType&&>(icon)
			, static_cast<IconType&&>(small_icon)
			, static_cast<CursorType&&>(cursor)
			, background
			, menu_name
		};
	}
}
