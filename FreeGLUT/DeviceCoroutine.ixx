export module Glib.Device.Coroutine;
export import Utility.Coroutine;
export import Glib.Device.Command;

export namespace gl::device
{
	template<typename T>
	class [[nodiscard]] Task
	{
	public:
		using task_type = Task<T>;

		// 규칙 1. C++에서 정의된 규칙을 구현한 promise_type 이라는 이름의 타입이 정의되어야 한다.
		struct [[nodiscard]] promise_type
		{
			using handle_type = std::coroutine_handle<promise_type>;

			// 사용자 정의 "코루틴 반환 객체"를 반환 한다
			task_type get_return_object() noexcept
			{
				return task_type{ handle_type::from_promise(*this) };
			}

			// 코루틴 최초 실행 시 호출. awaitable 객체를 반환 한다.
			auto initial_suspend() noexcept { return std::suspend_never{}; }

			// co_return을 사용하는 경우 구현. 나중에 코루틴 종료를 설명 할 때 같이 설명
			auto return_void() noexcept { return std::suspend_never{}; }

			// 코루틴 종료 시 호출. 나중에 코루틴 종료를 설명 할 때 같이 설명
			auto final_suspend() noexcept { return std::suspend_always{}; }

			// 코루틴 수행 중 예외 발생 시 호출
			void unhandled_exception() { std::exit(1); }

			template<typename U>
			std::suspend_always yield_value(U&& value) noexcept
			{
				this->value = static_cast<U&&>(value);
				return {};
			}

			T value;
		};

		using handle_type = promise_type::handle_type;

		Task() noexcept = default;

		// 규칙 2. std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다.
		handle_type co_handler;

		// 규칙 3. std::coroutine_handle<promise_type> 을 인자로 받아
		// 멤버 변수를 초기화 하는 생성자가 있어야 한다.
		Task(handle_type handler)
			: co_handler(handler)
		{}

		// 규칙 4. 소멸자에서 std::coroutine_handle<promise_type> 타입의
		// 코루틴 핸들러 멤버 변수의 destroy를 호출 해야 한다.
		~Task() noexcept
		{
			if (co_handler.done())
			{
				co_handler.destroy();
			}
		}
	};

	template<typename T>
	class [[nodiscard]] TestAwaiter
	{
	public:
		using type = TestAwaiter<T>;

		constexpr bool await_ready() const noexcept
		{
			return false;
		}

		constexpr void await_suspend(Task<T>::handle_type h) noexcept
		{
			handle = h;
		}

		constexpr void await_resume() const noexcept
		{}

		Task<T>::handle_type handle;
	};

	Task<int> test_coroutine1() noexcept
	{
		co_await std::suspend_always{};
	}

	struct [[nodiscard]] CommandCoroutine
	{
	public:
		void* rawHandle = nullptr;
	};
}
