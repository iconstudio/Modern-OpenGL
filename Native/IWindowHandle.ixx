module;
#include "Internal.hpp"

export module Glib.Device.IWindowHandle;
import <type_traits>;
import <string_view>;
import Glib.Definitions;
import Glib.Device.ProcessInstance;
import Glib.Device.IHandle;
import Glib.Device.Event;
import Glib.Device.IO;
import Glib.Device.IContext;

export namespace gl::device
{
	using native::HWND;

	class [[nodiscard]] IWindowHandle : public IHandle<HWND>
	{
	public:
		using base = IHandle<HWND>;
		using handle_type = base::handle_type;

		constexpr IWindowHandle() noexcept = default;

		constexpr IWindowHandle(IWindowHandle&& other) noexcept
			: base(std::move(other))
		{}

		explicit constexpr IWindowHandle(const handle_type& handle) noexcept
			: base(handle)
		{}

		explicit constexpr IWindowHandle(handle_type&& handle) noexcept
			: base(std::move(handle))
		{}

		constexpr IWindowHandle(nullptr_t) noexcept
			: base(nullptr)
		{}

		constexpr IWindowHandle& operator=(IWindowHandle&& other) noexcept
		{
			base::operator=(std::move(other));
			return *this;
		}

		constexpr IWindowHandle& operator=(handle_type&& handle) noexcept
		{
			base::operator=(std::move(handle));
			return *this;
		}

		bool StartUpdate() noexcept;

		long long DefaultWndProc(const unsigned int& msg, const unsigned long long& lhs, const long long& rhs) const noexcept;

		bool Destroy() noexcept;

		bool SendCommand(const unsigned int& id, const unsigned long long& lhs, const long long& rhs) const noexcept;

		bool SendCommand(const EventID& id, const unsigned long long& lhs, const long long& rhs) const noexcept;

		bool SendCommand(const Event& cmd) const noexcept;

		bool SendCommand(Event&& cmd) const noexcept;

		bool SendCommand(const EventID& id, const io::KeyCode& keycode, const io::KeyboardFlag& flags = io::KeyboardFlag::None) const noexcept;

		bool UICommand(const int& cmd) noexcept;

		bool Show() noexcept;

		bool Hide() noexcept;

		bool Maximize() noexcept;

		bool Minimize() noexcept;

		bool Restore() noexcept;

		bool Redraw(const bool& flag) noexcept;

		bool Close() noexcept;

		bool EnableInput() noexcept;

		bool DisableInput() noexcept;

		[[nodiscard]]
		DeviceContext AcquireContext() const noexcept;

		[[nodiscard]]
		RenderingContext AcquireRenderContext() const noexcept;

		bool ReleaseContext(DeviceContext& context) const noexcept;

		[[nodiscard]]
		IContext AcquireNativeContext() const noexcept;

		bool ReleaseNativeContext(IContext& context) const noexcept;

		[[nodiscard]]
		bool IsMinimized() const noexcept;

		[[nodiscard]]
		bool IsMaximized() const noexcept;

		[[nodiscard]]
		bool IsRestored() const noexcept;

		[[nodiscard]]
		bool IsInputEnabled() const noexcept;

		long long SetInternalValue(int index, const long long& value) const noexcept;

		long long SetInternalValue(int index, long long&& value) const noexcept;

		long long SetInternalUserData(const long long& value) const noexcept;

		long long SetInternalUserData(long long&& value) const noexcept;

		[[nodiscard]]
		long long GetInternalValue(int index) const noexcept;

		[[nodiscard]]
		long long GetInternalUserData() const noexcept;

		[[nodiscard]]
		unsigned long GetStyle() const noexcept;

		[[nodiscard]]
		unsigned long GetExStyle() const noexcept;

		[[nodiscard]]
		int GetID() const noexcept;

		[[nodiscard]]
		native::NativeRect GetDimensions() const noexcept;

		bool TryGetDimensions(native::NativeRect& output) const noexcept;

		IWindowHandle(const IWindowHandle&) = delete;
		IWindowHandle& operator=(const IWindowHandle&) = delete;
};

	[[nodiscard]]
	constexpr native::NativeRect MakeNativeRect() noexcept
	{
		return {};
	}

	[[nodiscard]]
	HWND__* MakeNativeWindow(const ProcessInstance& hinst
		, const std::wstring_view& class_name
		, const std::wstring_view& title
		, const unsigned long& styles
		, const unsigned long& options
		, const int& x
		, const int& y
		, const int& width
		, const int& height
		, const HWND& parent = nullptr
		, const HMENU& menu = nullptr
		, void* uparams = nullptr)
		noexcept;

	bool UnregisterWindow(const ProcessInstance& hinst, const std::wstring_view& class_name);

	void PostQuitMessage(const int& exit_code) noexcept;
}
