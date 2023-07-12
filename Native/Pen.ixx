export module Glib.Device.Resource.Pen;
import Glib.Definitions;
import Glib.Device.IGraphics;
import Glib.Device.Colour;

export namespace gl::win32::resource
{
	enum class [[nodiscard]] PenStyles
	{
		None = 5,// PS_NULL
		Fill = 0, // PS_SOLID
		Dash = 1, // PS_DASH
		Dots = 2, // PS_DOT
		DashDot = 3, // PS_DASHDOT
		//Frame = 6, // PS_INSIDEFRAME
	};

	class [[nodiscard]] Pen : public IGraphics<Pen, native::RawPen>
	{
	public:
		using base = IGraphics<Pen, native::RawPen>;

		Pen(const PenStyles& style, const int& width, const Colour& color) noexcept;
		Pen(const PenStyles& style, const int& width, Colour&& color) noexcept;
		Pen(const PenStyles& style, const int& width, const RawRGB& color) noexcept;
		Pen(const PenStyles& style, const int& width, RawRGB&& color) noexcept;
		~Pen() noexcept;

		void Destroy() noexcept;

		[[nodiscard]] const PenStyles& GetStyle() const& noexcept;
		[[nodiscard]] PenStyles&& GetStyle() && noexcept;
		[[nodiscard]] const int& GetSize() const& noexcept;
		[[nodiscard]] int&& GetSize() && noexcept;
		[[nodiscard]] Colour& GetColor() & noexcept;
		[[nodiscard]] const Colour& GetColor() const& noexcept;
		[[nodiscard]] Colour&& GetColor() && noexcept;
		[[nodiscard]] const Colour&& GetColor() const&& noexcept;

		Pen& operator=(nullptr_t) noexcept;

		Pen(const Pen&) = delete;
		Pen(Pen&&) = delete;
		Pen& operator=(const Pen&&) = delete;
		Pen& operator=(Pen&&) = delete;

	private:
		PenStyles myStyle; // not modifiable
		int mySize; // not modifiable
		Colour myColor; // modifiable
	};
}
