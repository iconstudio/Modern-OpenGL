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

		// ��Ģ 1. C++���� ���ǵ� ��Ģ�� ������ promise_type �̶�� �̸��� Ÿ���� ���ǵǾ�� �Ѵ�.
		struct [[nodiscard]] promise_type
		{
			using handle_type = std::coroutine_handle<promise_type>;

			// ����� ���� "�ڷ�ƾ ��ȯ ��ü"�� ��ȯ �Ѵ�
			task_type get_return_object() noexcept
			{
				return task_type{ handle_type::from_promise(*this) };
			}

			// �ڷ�ƾ ���� ���� �� ȣ��. awaitable ��ü�� ��ȯ �Ѵ�.
			auto initial_suspend() noexcept { return std::suspend_never{}; }

			// co_return�� ����ϴ� ��� ����. ���߿� �ڷ�ƾ ���Ḧ ���� �� �� ���� ����
			auto return_void() noexcept { return std::suspend_never{}; }

			// �ڷ�ƾ ���� �� ȣ��. ���߿� �ڷ�ƾ ���Ḧ ���� �� �� ���� ����
			auto final_suspend() noexcept { return std::suspend_always{}; }

			// �ڷ�ƾ ���� �� ���� �߻� �� ȣ��
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

		// ��Ģ 2. std::coroutine_handle<promise_type> Ÿ���� ��� ������ �־�� �Ѵ�.
		handle_type co_handler;

		// ��Ģ 3. std::coroutine_handle<promise_type> �� ���ڷ� �޾�
		// ��� ������ �ʱ�ȭ �ϴ� �����ڰ� �־�� �Ѵ�.
		Task(handle_type handler)
			: co_handler(handler)
		{}

		// ��Ģ 4. �Ҹ��ڿ��� std::coroutine_handle<promise_type> Ÿ����
		// �ڷ�ƾ �ڵ鷯 ��� ������ destroy�� ȣ�� �ؾ� �Ѵ�.
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
