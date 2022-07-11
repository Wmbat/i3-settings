#include <libi3-settings/utils/enums.hpp>

#include <catch2/catch_test_macros.hpp>

enum struct fruit
{
	apple,
	banana,
	orange
};

SCENARIO("converting to the underlying type of a default scoped enum", "[enum]")
{
	GIVEN("A bunch of enum values")
	{
		fruit apple = fruit::apple;
		fruit banana = fruit::banana;
		fruit orange = fruit::orange;

		WHEN("Converting the enum values")
		{
			auto apple_val = i3s::to_underlying(apple);
			auto banana_val = i3s::to_underlying(banana);
			auto orange_val = i3s::to_underlying(orange);

			THEN("The values should correspond to the enum position")
			{
				CHECK(apple_val == 0);
				CHECK(banana_val == 1);
				CHECK(orange_val == 2);
			}
		}
	}
}

enum struct drink : std::int8_t
{

};

enum vegetable
{

};

class dinnerware
{
};

static_assert(i3s::is_scoped_enum<fruit>::value);
static_assert(i3s::is_scoped_enum<drink>::value);
static_assert(!i3s::is_scoped_enum<int>::value);
static_assert(!i3s::is_scoped_enum<vegetable>::value);
static_assert(!i3s::is_scoped_enum<dinnerware>::value);
static_assert(!i3s::is_scoped_enum<std::string>::value);

static_assert(i3s::is_scoped_enum_v<fruit>);
static_assert(i3s::is_scoped_enum_v<drink>);
static_assert(!i3s::is_scoped_enum_v<int>);
static_assert(!i3s::is_scoped_enum_v<vegetable>);
static_assert(!i3s::is_scoped_enum_v<dinnerware>);
static_assert(!i3s::is_scoped_enum_v<std::string>);
