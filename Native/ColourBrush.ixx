export module Glib.Device.Brush;
import <type_traits>;
import Glib.Device.Definitions;
import Glib.Device.IHandle;

export namespace gl::device
{
	class [[nodiscard]] ColorBrush : public IHandle<native::NativeColorBrush>
	{
	public:
		using base = IHandle<native::NativeColorBrush>;

		constexpr ColorBrush() noexcept = default;

		constexpr ColorBrush(nullptr_t) noexcept
			: base(nullptr)
		{}

		explicit constexpr ColorBrush(const handle_type& brush) noexcept
			: base(brush)
		{}

		explicit constexpr ColorBrush(handle_type&& brush) noexcept
			: base(std::move(brush))
		{}

		~ColorBrush() noexcept;

		void Destroy() noexcept;

		constexpr ColorBrush& operator=(const handle_type& brush) noexcept
		{
			base::operator=(brush);
			return *this;
		}

		constexpr ColorBrush& operator=(handle_type&& brush) noexcept
		{
			base::operator=(std::move(brush));
			return *this;
		}

		ColorBrush& operator=(nullptr_t) noexcept;

		ColorBrush(const ColorBrush&) = delete;
		constexpr ColorBrush(ColorBrush&&) noexcept = default;
		ColorBrush& operator=(const ColorBrush&) = delete;
		constexpr ColorBrush& operator=(ColorBrush&&) noexcept = default;
	};

	enum class [[nodiscard]] PatternBrushType
	{
		Horizontal = 0, // HS_HORIZONTAL
		Vertical = 1, // HS_VERTICAL
		DownDiagonal = 2, // HS_FDIAGONAL
		UpDiagonal = 3, // HS_BDIAGONAL
		Cross = 4, // HS_CROSS,
		CrossDiagonal = 5, // HS_DIAGCROSS
	};

	[[nodiscard]]
	ColorBrush MakeColorBrush(const unsigned long& color) noexcept;

	[[nodiscard]]
	ColorBrush MakeColorBrush(unsigned long&& color) noexcept;

	[[nodiscard]]
	ColorBrush MakePatternBrush(const native::RawBitmap& image) noexcept;

	[[nodiscard]]
	ColorBrush MakeStampBrush(const PatternBrushType& pattern) noexcept;
}
