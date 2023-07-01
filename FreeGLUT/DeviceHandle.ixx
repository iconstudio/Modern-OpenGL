module;
#include "Internal.hpp"

export module Glib.Device.Handle;
import <type_traits>;
import <string_view>;
import Glib.Device.IHandle;
import Glib.Device.Event.API;
export import Glib.Device.IO;

export namespace gl::device
{
	using RawDeviceHandle = ::HWND__*;
	using HWND = ::HWND__*;
	using NativeRect = ::tagRECT;

	struct [[nodiscard]] log_t { constexpr log_t() noexcept = default; };
	inline constexpr log_t log{};

	class [[nodiscard]] DeviceHandle : public IHandle<RawDeviceHandle>
	{
	public:
		using base = IHandle<RawDeviceHandle>;
		using handle_type = base::handle_type;

		constexpr DeviceHandle()
			: base()
		{}

		constexpr DeviceHandle(nullptr_t) noexcept
			: base(nullptr)
		{}

		explicit constexpr DeviceHandle(handle_type const& handle) noexcept
			: base(handle)
		{}

		explicit constexpr DeviceHandle(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		constexpr DeviceHandle& operator=(nullptr_t) noexcept
		{
			base::myHandle = nullptr;
			return *this;
		}

		constexpr DeviceHandle& operator=(handle_type&& handle) noexcept
		{
			base::myHandle = std::move(handle);
			return *this;
		}

		~DeviceHandle() noexcept
		{
			if (myHandle)
			{
				// TODO: replace with new interface
				//::DestroyWindow(myHandle);
				myHandle = nullptr;
			}
		}

		inline bool StartUpdate() noexcept
		{
			return 0 != ::UpdateWindow(myHandle);
		}

		long long DefaultWndProc(const unsigned int& msg, const unsigned long long& lhs, const long long& rhs) const noexcept
		{
			return ::DefWindowProc(myHandle, msg, lhs, rhs);
		}

		inline bool SendCommand(const unsigned int& id, const unsigned long long& lhs, const long long& rhs) const
			noexcept
		{
			return EventAPI::Push(myHandle, id, lhs, rhs);
		}

		inline bool SendCommand(const EventID& id, const unsigned long long& lhs, const long long& rhs) const
			noexcept
		{
			return EventAPI::Push(myHandle, id, lhs, rhs);
		}

		inline bool SendCommand(const Event& cmd) const
			noexcept
		{
			return EventAPI::Push(myHandle, cmd);
		}

		inline bool SendCommand(Event&& cmd) const
			noexcept
		{
			return EventAPI::Push(myHandle, static_cast<Event&&>(cmd));
		}

		inline bool SendCommand(const EventID& id, const int& keycode, const long long& flags = 0) const
			noexcept
		{
			return SendCommand(id, static_cast<unsigned long long>(keycode), flags);
		}

		inline bool SendCommand(const EventID& id, const io::KeyCode& keycode, const io::KeyboardFlag& flags = io::KeyboardFlag::None) const
			noexcept
		{
			return SendCommand(id, static_cast<unsigned long long>(keycode), static_cast<long long>(flags));
		}

		inline bool UICommand(const int& cmd) noexcept
		{
			return 0 != ::ShowWindow(myHandle, cmd);
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
			return SendCommand(WM_SETREDRAW, static_cast<WPARAM>(flag), 0);
		}

		inline bool EnableInput() noexcept
		{
			return 0 != ::EnableWindow(myHandle, TRUE);
		}

		inline bool DisableInput() noexcept
		{
			return 0 != ::EnableWindow(myHandle, FALSE);
		}

		inline bool Close() noexcept
		{
			return SendCommand(WM_CLOSE, 0, 0);
		}

		[[nodiscard]]
		inline bool IsMinimized() const noexcept
		{
			return 0 != IsIconic(myHandle);
		}

		[[nodiscard]]
		inline bool IsMaximized() const noexcept
		{
			return 0 != IsZoomed(myHandle);
		}

		[[nodiscard]]
		inline bool IsRestored() const noexcept
		{
			return 0L == (GetStyle() & (WS_MINIMIZE | WS_MAXIMIZE));
		}

		[[nodiscard]]
		inline bool IsInputEnabled() const noexcept
		{
			return 0 != ::IsWindowEnabled(myHandle);
		}

		inline long long SetInternalValue(int index, const long long& value) const noexcept
		{
			return ::SetWindowLongPtr(myHandle, index, value);
		}

		inline long long SetInternalValue(int index, long long&& value) const noexcept
		{
			return ::SetWindowLongPtr(myHandle, index, std::move(value));
		}

		[[nodiscard]]
		inline long long GetInternalValue(int index) const noexcept
		{
			return ::GetWindowLongPtr(myHandle, index);
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
			::GetWindowRect(myHandle, &rect);
			return rect;
		}

		[[nodiscard]]
		inline bool TryGetDimensions(NativeRect& output) const noexcept
		{
			return 0 != ::GetWindowRect(myHandle, &output);
		}

		DeviceHandle(const DeviceHandle&) = delete;
		constexpr DeviceHandle(DeviceHandle&&) noexcept = default;
		DeviceHandle& operator=(const DeviceHandle&) = delete;
		constexpr DeviceHandle& operator=(DeviceHandle&&) noexcept = default;
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
