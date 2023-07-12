export module Glib.Window.Coroutine;
import Utility.Constraints;
import Utility.FixedString;
import Utility.Coroutine;

export namespace gl::win32
{
	using util::coroutine::coroutine_handle;
	using util::coroutine::awaitable;
	using util::coroutine::suspend_always;
	using util::coroutine::suspend_never;
	using util::coroutine::Cowork;
	using util::coroutine::coexecution;
	using util::coroutine::default_sentinel_t;
	using util::coroutine::DeferredPromise;
	using util::coroutine::RelaxedPromise;

	struct [[nodiscard]] WaitForSeconds
	{
		constexpr WaitForSeconds(long long ms) noexcept
			: milliSeconds(ms)
		{}

		constexpr bool await_ready() const noexcept { return false; }

		constexpr void await_suspend(coroutine_handle<>) const noexcept {}

		constexpr void await_resume() const noexcept {}

		long long milliSeconds;
	};

	class [[nodiscard]] Coroutine
	{
	public:
		struct promise_type;
		using handle_type = util::coroutine::coroutine_handle<promise_type>;

		struct promise_type
		{
			Coroutine get_return_object() noexcept
			{
				return Coroutine{ handle_type::from_promise(*this) };
			}

			auto yield_value(const WaitForSeconds& wait) noexcept
			{
				return wait;
			}

			static suspend_always initial_suspend() noexcept
			{
				return {};
			}

			static suspend_always final_suspend() noexcept
			{
				return {};
			}

			static void return_void() noexcept {}

			static void unhandled_exception() noexcept {}
		};

		constexpr Coroutine() noexcept = default;

		~Coroutine() noexcept
		{
			if (myHandle)
			{
				myHandle.destroy();
			}
		}

		explicit constexpr Coroutine(handle_type coroutine)
			noexcept
			: myHandle(coroutine)
		{}

		void Resume() const noexcept
		{
			if (!IsEmpty() && !IsDone())
			{
				myHandle.resume();
			}
		}

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

		handle_type myHandle;
	};
}
