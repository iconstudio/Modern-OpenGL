module;
#include <winrt/windows.ui.composition.h>
#include <winrt/Windows.ui.viewmanagement.h>
module Glib.Device.Display;

namespace gl::device
{
	namespace dim
	{
		void FindDimmingMode()
		{
			using namespace winrt::Windows::UI::ViewManagement;

			UISettings settings = UISettings();
			const Colour col_a_0 = settings.GetColorValue(UIColorType::Accent);
			const Colour col_a_1 = settings.GetColorValue(UIColorType::AccentDark1);
			const Colour col_a_2 = settings.GetColorValue(UIColorType::AccentDark2);
			const Colour col_a_3 = settings.GetColorValue(UIColorType::AccentDark3);
			const Colour col_a_4 = settings.GetColorValue(UIColorType::AccentLight1);
			const Colour col_a_5 = settings.GetColorValue(UIColorType::AccentLight2);
			const Colour col_a_6 = settings.GetColorValue(UIColorType::AccentLight3);
			const Colour col_fg = settings.GetColorValue(UIColorType::Foreground);
			const Colour col_bk = settings.GetColorValue(UIColorType::Background);

			if (IsColorBright(col_fg))
			{
				//util::Println("Dark Mode");
			}
			else
			{
				//util::Println("Light Mode");
			}
		}
	}
}
