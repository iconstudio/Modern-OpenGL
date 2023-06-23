export module Glib.Device.Coroutine;
export import Utility.Coroutine;
export import Glib.Device.Command;

export namespace gl::device
{
	struct [[nodiscard]] CommandCoroutine
	{
	public:
		static inline
			util::coroutine::RelaxedTask
			Process(const DeviceCommand& msg)
			noexcept
		{

		}
	};
}
