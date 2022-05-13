#include <libi3-settings/defines.hpp>
#include <libi3-settings/utils/flag.hpp>

#include <catch2/catch.hpp>

enum struct fruit_salad
{
	banana = 1 << 0,
	apple = 1 << 1,
	lemon = 1 << 2,
	guava = 1 << 3
};

using fruit_salad_flag = i3s::flag<fruit_salad>;

template <>
struct i3s::flag_traits<fruit_salad>
{
	enum struct traits : fruit_salad_flag::underlying_type
	{
		all_bits = static_cast<fruit_salad_flag::underlying_type>(fruit_salad::banana)
				   | static_cast<fruit_salad_flag::underlying_type>(fruit_salad::apple)
				   | static_cast<fruit_salad_flag::underlying_type>(fruit_salad::lemon)
				   | static_cast<fruit_salad_flag::underlying_type>(fruit_salad::guava)
	};

	using enum traits;
};

I3S_DEFINE_EXTRA_ENUM_OPERATORS(fruit_salad_flag)

TEST_CASE("comparison", "[flag]")
{
	SECTION("less than") {}
	SECTION("less than or equal") {}
	SECTION("greater than") {}
	SECTION("greater than or equal") {}
	SECTION("equal") {}
}
