#include <libi3-settings/defines.hpp>
#include <libi3-settings/utils/flag.hpp>

#include <catch2/catch_test_macros.hpp>

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

// TODO(wmbat): Need to add checking of all operators

SCENARIO("comparing flags", "[flag]")
{
	GIVEN("an assortment of fruit salads")
	{
		auto const salad_1 = fruit_salad::apple | fruit_salad::banana;
		auto const salad_2 = fruit_salad::apple | fruit_salad::banana | fruit_salad::lemon;
		auto const salad_3 = fruit_salad::apple | fruit_salad::banana | fruit_salad::lemon;

		WHEN("comparing a 2 fruit salad to a 3 fruit salad")
		{
			bool lt = salad_1 < salad_2;
			bool lte = salad_1 <= salad_2;
			bool gt = salad_2 > salad_1;
			bool gte = salad_2 >= salad_1;
			bool eq = salad_2 == salad_1;
			bool neq = salad_2 != salad_1;

			THEN("the 2 fruit salad should be smaller than then 3 fruit salad")
			{
				CHECK(lt);
				CHECK(lte);
				CHECK(gt);
				CHECK(gte);
				CHECK(not eq);
				CHECK(neq);
			}
		}

		WHEN("comparing two identical fruit salads")
		{
			bool lt = salad_2 < salad_3;
			bool lte = salad_2 <= salad_3;
			bool gt = salad_3 > salad_2;
			bool gte = salad_3 >= salad_2;
			bool eq = salad_3 == salad_2;
			bool neq = salad_3 != salad_2;

			THEN("the fruit salads should be the same")
			{
				CHECK(not lt);
				CHECK(lte);
				CHECK(not gt);
				CHECK(gte);
				CHECK(eq);
				CHECK(not neq);
			}
		}
	}
}
