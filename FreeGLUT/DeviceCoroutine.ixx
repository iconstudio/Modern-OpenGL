module;
#include "Internal.hpp"

export module Glib.Device.Coroutine;
import Utility.Coroutine;
import Utility.Coroutine.Logic;
export import Utility.Concurrency.Thread;
export import Glib.Device.Handle;
import Glib.Device.Command;

namespace gl::device
{
	bool Process(const ::HWND& handle) noexcept;

	export inline auto
		CreateQueue(const HWND& handle, util::stop_token&& canceller)
		noexcept
	{
		const auto stopper = [canceller = std::move(canceller)]() noexcept -> bool {
			return !canceller.stop_requested();
		};

		return util::corepeat_as_if<util::coexecution::Later>(Process, stopper, handle);
	}

	export inline auto
		CreateQueue(const HWND& handle)
		noexcept
	{
		return util::corepeat_as<util::coexecution::Later>(Process, handle);
	}

	export inline
		auto
		CreateQueueAndStart(const ::HWND& handle, util::stop_token&& canceller)
		noexcept
	{
		auto queue = CreateQueue(handle, std::move(canceller));
		queue();

		return queue;
	}

	bool Process(const ::HWND& handle) noexcept
	{
		DeviceCommand cmd{};

		if (auto result = DeviceCommandAPI::Pop(handle, cmd); MsgResult::Quit != result)
		{
			if (MsgResult::Unknown == result)
			{
				return false;
			}

			DeviceCommandAPI::Process(cmd);
			return true;
		}
		else
		{
			return false;
		}
	}
}
