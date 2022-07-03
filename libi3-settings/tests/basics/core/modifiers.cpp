#include <libi3-settings/core/modifiers.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("string formatting", "[modifiers]")
{
	SECTION("enum value")
	{
		REQUIRE("mod1" == fmt::format("{}", i3s::modifier::mod1));
		REQUIRE("mod2" == fmt::format("{}", i3s::modifier::mod2));
		REQUIRE("mod3" == fmt::format("{}", i3s::modifier::mod3));
		REQUIRE("mod4" == fmt::format("{}", i3s::modifier::mod4));
		REQUIRE("mod5" == fmt::format("{}", i3s::modifier::mod5));
		REQUIRE("shift" == fmt::format("{}", i3s::modifier::shift));
		REQUIRE("ctrl" == fmt::format("{}", i3s::modifier::ctrl));
	}

	SECTION("single bit flag")
	{
		REQUIRE("mod1" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod1)));
		REQUIRE("mod2" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod2)));
		REQUIRE("mod3" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod3)));
		REQUIRE("mod4" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod4)));
		REQUIRE("mod5" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod5)));
		REQUIRE("shift" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::shift)));
		REQUIRE("ctrl" == fmt::format("{}", i3s::modifier_flag(i3s::modifier::ctrl)));
	}

	SECTION("multiple bits flag")
	{
		auto const flag1 =
			fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod1) | i3s::modifier::ctrl);
		auto const full_ordered_flag =
			fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod1) | i3s::modifier::mod2
								  | i3s::modifier::mod3 | i3s::modifier::mod4 | i3s::modifier::mod5
								  | i3s::modifier::shift | i3s::modifier::ctrl);
		auto const full_unordered_flag =
			fmt::format("{}", i3s::modifier_flag(i3s::modifier::mod4) | i3s::modifier::mod3
								  | i3s::modifier::mod1 | i3s::modifier::mod5 | i3s::modifier::mod2
								  | i3s::modifier::shift | i3s::modifier::ctrl);

		REQUIRE(flag1 == "mod1+ctrl");
		REQUIRE(full_ordered_flag == "mod1+mod2+mod3+mod4+mod5+shift+ctrl");
		REQUIRE(full_unordered_flag == "mod1+mod2+mod3+mod4+mod5+shift+ctrl");
	}
}
