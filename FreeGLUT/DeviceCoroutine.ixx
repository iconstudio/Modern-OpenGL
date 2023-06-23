module;
#include "Internal.hpp"

export module Glib.Device.Coroutine;
export import Utility.Coroutine;
export import Utility.Concurrency.Thread;
export import Glib.Device.Command;

export namespace gl::device
{
	struct [[nodiscard]] CommandCoroutine
	{
	public:
		static inline
			auto
			CreateQueue(const HWND& handle, util::stop_token&& canceller)
			noexcept
		{
			const auto getter_result = [&]() noexcept -> bool {
				if (canceller.stop_requested())
				{

					return false;
				}
			};

			return util::corepeat_as<util::coexecution::Later>(Process, handle);
		}

		static inline
			auto
			CreateQueue(const HWND& handle)
			noexcept
		{
			return util::corepeat_as<util::coexecution::Later>(Process, handle);
		}

		static inline
			auto
			CreateQueueAndStart(const ::HWND& handle, util::stop_token&& canceller)
			noexcept
		{
			auto queue = CreateQueue(handle, std::move(canceller));
			queue();

			return queue;
		}

	private:
		static inline bool Process(const ::HWND& handle) noexcept
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
	};
}
