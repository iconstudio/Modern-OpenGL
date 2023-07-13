export module Glib.Rect;

export namespace gl
{
	struct [[nodiscard]] Rect
	{
		constexpr Rect() noexcept = default;
		constexpr ~Rect() noexcept = default;

		constexpr Rect(const int& mx, const int& my, const int& width, const int& height)
			noexcept
			: x(mx), y(my), w(width), h(height)
		{}

		constexpr Rect(int&& mx, int&& my, const int& width, const int& height)
			noexcept
			: x(static_cast<int&&>(mx)), y(static_cast<int&&>(my)), w(width), h(height)
		{}

		constexpr Rect(const int& mx, const int& my, int&& width, int&& height)
			noexcept
			: x(mx), y(my), w(static_cast<int&&>(width)), h(static_cast<int&&>(height))
		{}

		constexpr Rect(int&& mx, int&& my, int&& width, int&& height)
			noexcept
			: x(static_cast<int&&>(mx)), y(static_cast<int&&>(my)), w(static_cast<int&&>(width)), h(static_cast<int&&>(height))
		{}

		constexpr Rect(const Rect& other) noexcept = default;
		constexpr Rect& operator=(const Rect& other) noexcept = default;
		constexpr Rect(Rect&& other) noexcept = default;
		constexpr Rect& operator=(Rect&& other) noexcept = default;

		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
	};
}
