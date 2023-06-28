export module Glib.Window.Coroutine;
import Utility.Coroutine;

export namespace gl::window
{
	using util::coroutine::coroutine_handle;

	class [[nodiscard]] Coroutine
	{
	public:
		using handle_type = util::coroutine::coroutine_handle<void>;

		constexpr Coroutine() noexcept = default;

		~Coroutine() noexcept
		{
			if (myHandle.done())
			{
				myHandle.destroy();
			}
		}

		explicit constexpr Coroutine(handle_type coroutine)
			noexcept
			: myHandle(coroutine)
		{}

		[[nodiscard]]
		bool IsDone() const noexcept
		{
			return myHandle.done();
		}

		[[nodiscard]]
		bool IsEmpty() const noexcept
		{
			return !myHandle;
		}

		Coroutine(const Coroutine& other) = delete;
		constexpr Coroutine(Coroutine&& other) noexcept = default;
		Coroutine& operator=(const Coroutine& other) = delete;
		constexpr Coroutine& operator=(Coroutine&& other) noexcept = default;

		void* myFunctor;
		handle_type myHandle;
	};
}
