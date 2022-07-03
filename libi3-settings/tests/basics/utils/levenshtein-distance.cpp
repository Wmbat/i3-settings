#include <libi3-settings/utils/levenshtein-distance.hpp>

#include <catch2/catch_test_macros.hpp>

SCENARIO("when ", "[levenshtein]")
{
	std::string str0 = "hello";

	GIVEN("a string with 1 different letter")
	{
		std::string str1 = "hella";

		THEN("The levenshtein distance should be 1")
		{
			CHECK(i3s::levenshtein_distance(str0, str1) == 1);
		}
	}

	GIVEN("a string with 1 swapped letter")
	{
		std::string str1 = "helol";

		THEN("The levenshtein distance should be 1")
		{
			CHECK(i3s::levenshtein_distance(str0, str1) == 1);
		}
	}

	GIVEN("a string with 1 different & 1 swapped letter")
	{
		std::string str1 = "helal";

		THEN("The levenshtein distance should be 2")
		{
			CHECK(i3s::levenshtein_distance(str0, str1) == 2);
		}
	}

	GIVEN("2 completely different strings")
	{
		std::string str1 = "watts";

		THEN("The levenshtein distance should be 1")
		{
			CHECK(i3s::levenshtein_distance(str0, str1) == 5);
		}
	}
}
