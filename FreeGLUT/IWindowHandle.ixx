module;
#include "Internal.hpp"

export module Glib.Device.IWindowHandle;
import <type_traits>;
import <string_view>;
import Glib.Device.IHandle;
export import Glib.Device.Event;
import Glib.Device.Event.API;
export import Glib.Device.IO;

export namespace gl::device
{
	using RawDeviceHandle = ::HWND__*;
	using HWND = ::HWND__*;
	using NativeRect = tagRECT;

	class [[nodiscard]] IWindowHandle : public IHandle<RawDeviceHandle>
	{
	public:
		using base = IHandle<RawDeviceHandle>;
		using handle_type = base::handle_type;

		constexpr IWindowHandle() noexcept = default;

		constexpr IWindowHandle(nullptr_t) noexcept
			: base(nullptr)
		{}

		constexpr IWindowHandle(const handle_type& handle) noexcept
			: base(handle)
		{}

		constexpr IWindowHandle(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		inline bool StartUpdate() noexcept
		{
			return 0 != Delegate(::UpdateWindow);
		}

		long long DefaultWndProc(const unsigned int& msg, const unsigned long long& lhs, const long long& rhs) const noexcept
		{
			return Delegate(::DefWindowProc, msg, lhs, rhs);
		}

		inline bool SendCommand(const unsigned int& id, const unsigned long long& lhs, const long long& rhs) const
			noexcept
		{
			return EventAPI::Push(GetHandle(), id, lhs, rhs);
		}

		inline bool SendCommand(const EventID& id, const unsigned long long& lhs, const long long& rhs) const
			noexcept
		{
			return EventAPI::Push(GetHandle(), id, lhs, rhs);
		}

		inline bool SendCommand(const Event& cmd) const
			noexcept
		{
			return EventAPI::Push(GetHandle(), cmd);
		}

		inline bool SendCommand(Event&& cmd) const
			noexcept
		{
			return EventAPI::Push(GetHandle(), static_cast<Event&&>(cmd));
		}

		inline bool SendCommand(const EventID& id, const io::KeyCode& keycode, const io::KeyboardFlag& flags = io::KeyboardFlag::None) const
			noexcept
		{
			return SendCommand(id, static_cast<unsigned long long>(keycode), static_cast<long long>(flags));
		}

		inline bool UICommand(const int& cmd) noexcept
		{
			return 0 != Delegate(::ShowWindow, cmd);
		}

		inline bool Show() noexcept
		{
			return UICommand(SW_SHOW);
		}

		inline bool Hide() noexcept
		{
			return UICommand(SW_HIDE);
		}

		inline bool Maximize() noexcept
		{
			return UICommand(SW_MAXIMIZE);
		}

		inline bool Minimize() noexcept
		{
			return UICommand(SW_MINIMIZE);
		}

		inline bool Restore() noexcept
		{
			return UICommand(SW_RESTORE);
		}

		inline bool Redraw(const bool& flag) noexcept
		{
			return SendCommand(EventID::SetRedraw, static_cast<WPARAM>(flag), 0);
		}

		inline bool Close() noexcept
		{
			return SendCommand(EventID::Close, 0, 0);
		}

		inline bool EnableInput() noexcept
		{
			return 0 != Delegate(::EnableWindow, TRUE);
		}

		inline bool DisableInput() noexcept
		{
			return 0 != Delegate(::EnableWindow, FALSE);
		}

		[[nodiscard]]
		inline bool IsMinimized() const noexcept
		{
			return 0 != Delegate(::IsIconic);
		}

		[[nodiscard]]
		inline bool IsMaximized() const noexcept
		{
			return 0 != Delegate(::IsZoomed);
		}

		[[nodiscard]]
		inline bool IsRestored() const noexcept
		{
			return 0L == (GetStyle() & (WS_MINIMIZE | WS_MAXIMIZE));
		}

		[[nodiscard]]
		inline bool IsInputEnabled() const noexcept
		{
			return 0 != Delegate(::IsWindowEnabled);
		}

		inline long long SetInternalValue(int index, const long long& value) const noexcept
		{
			return Delegate(::SetWindowLongPtr, index, value);
		}

		inline long long SetInternalValue(int index, long long&& value) const noexcept
		{
			return Delegate(::SetWindowLongPtr, index, std::move(value));
		}

		[[nodiscard]]
		inline long long GetInternalValue(int index) const noexcept
		{
			return Delegate(::GetWindowLongPtr, index);
		}

		[[nodiscard]]
		inline long long GetInternalUserData() const noexcept
		{
			return GetInternalValue(GWLP_USERDATA);
		}

		[[nodiscard]]
		inline unsigned long GetStyle() const noexcept
		{
			return static_cast<DWORD>(GetInternalValue(GWL_STYLE));
		}

		[[nodiscard]]
		inline unsigned long GetExStyle() const noexcept
		{
			return static_cast<DWORD>(GetInternalValue(GWL_EXSTYLE));
		}

		[[nodiscard]]
		inline int GetID() const noexcept
		{
			return static_cast<int>(GetInternalValue(GWLP_ID));
		}

		[[nodiscard]]
		inline NativeRect GetDimensions() const noexcept
		{
			NativeRect rect;
			Delegate(::GetWindowRect, &rect);
			return rect;
		}

		[[nodiscard]]
		inline bool TryGetDimensions(NativeRect& output) const noexcept
		{
			return 0 != Delegate(::GetWindowRect, &output);
		}

		IWindowHandle(const IWindowHandle&) = delete;
		constexpr IWindowHandle(IWindowHandle&&) noexcept = default;
		IWindowHandle& operator=(const IWindowHandle&) = delete;
		constexpr IWindowHandle& operator=(IWindowHandle&&) noexcept = default;
	};

	[[nodiscard]]
	constexpr NativeRect MakeNativeRect() noexcept
	{
		return {};
	}

	inline bool RegisterWindow(const tagWNDCLASSEXW& property)
	{
		return 0 == ::RegisterClassEx(&property);
	}

	inline bool UnregisterWindow(const HINSTANCE& hinst, const std::wstring_view& class_name)
	{
		return 0 == ::UnregisterClass(class_name.data(), hinst);
	}

	using ::PostQuitMessage;
	using ::DestroyWindow;
	using ::GetLastError;
}
