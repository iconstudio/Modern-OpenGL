module;
#include <winrt/windows.ui.composition.h>
#include <winrt/Windows.ui.viewmanagement.h>
module Glib.Display;
import Glib.Rect;
import Glib.Device.Colour;

using namespace winrt::Windows::UI::ViewManagement;

namespace gl::display
{
	using DisplayProperty = winrt::Windows::UI::ViewManagement::UISettings;

	[[nodiscard]]
	DisplayProperty AcquireSettings() noexcept;

	bool IsDimmingMode()
	{
		DisplayProperty settings = AcquireSettings();
		//const device::Colour col_a_0 = settings.GetColorValue(UIColorType::Accent);
		//const device::Colour col_a_1 = settings.GetColorValue(UIColorType::AccentDark1);
		//const device::Colour col_a_2 = settings.GetColorValue(UIColorType::AccentDark2);
		//const device::Colour col_a_3 = settings.GetColorValue(UIColorType::AccentDark3);
		//const device::Colour col_a_4 = settings.GetColorValue(UIColorType::AccentLight1);
		//const device::Colour col_a_5 = settings.GetColorValue(UIColorType::AccentLight2);
		//const device::Colour col_a_6 = settings.GetColorValue(UIColorType::AccentLight3);
		const device::Colour col_fg = settings.GetColorValue(UIColorType::Foreground);
		//const device::Colour col_bk = settings.GetColorValue(UIColorType::Background);

		if (device::IsColorBright(col_fg))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	DisplayProperty AcquireSettings() noexcept
	{
		return {};
	}
}
