export module Glib.Rect;

export extern "C" namespace gl
{
	struct [[nodiscard]] Rect
	{
		constexpr Rect() noexcept = default;
		constexpr ~Rect() noexcept = default;

		constexpr Rect(const int& x, const int& y, const int& width, const int& height)
			noexcept
			: x(x), y(y), w(width), h(height)
		{}

		constexpr Rect(int&& x, int&& y, const int& width, const int& height)
			noexcept
			: x(static_cast<int&&>(x)), y(static_cast<int&&>(y)), w(width), h(height)
		{}

		constexpr Rect(const int& x, const int& y, int&& width, int&& height)
			noexcept
			: x(x), y(y), w(static_cast<int&&>(width)), h(static_cast<int&&>(height))
		{}

		constexpr Rect(int&& x, int&& y, int&& width, int&& height)
			noexcept
			: x(static_cast<int&&>(x)), y(static_cast<int&&>(y)), w(static_cast<int&&>(width)), h(static_cast<int&&>(height))
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
