#include <libi3-settings/parsing/scanning.hpp>

#include <catch2/catch.hpp>

SCENARIO("Scanning data with no comments or empty lines", "[parsing][scanning]")
{
	GIVEN("Some data")
	{
		auto const data = std::string("bindsym $mod+$left focus left\n"
									  "bindsym $mod+$down focus down\n"
									  "bindsym $mod+$up focus up\n"
									  "bindsym $mod+$right focus right");

		WHEN("Scanning 4 lines of data")
		{
			auto const lines = i3s::parsing::scan_data(data);

			THEN("The scanning should return 4 lines") { CHECK(lines.size() == 4); }
		}
	}
}

SCENARIO("Scanning data with empty lines", "[parsing][scanning]")
{
	GIVEN("4 lines of valid data & 2 empty lines")
	{
		auto const data = std::string("bindsym $mod+$left focus left\n"
									  "bindsym $mod+$down focus down\n\n"
									  "bindsym $mod+$up focus up\n\n"
									  "bindsym $mod+$right focus right");

		WHEN("Scanning the data")
		{
			auto const lines = i3s::parsing::scan_data(data);

			THEN("The scanning should return 4 lines") { CHECK(lines.size() == 4); }
		}
	}
}

SCENARIO("Scanning data with comments", "[parsing][scanning]")
{
	GIVEN("4 lines of valid data & 4 lines of comments")
	{
		auto const data = std::string("# This is the 1st comment\n"
									  "bindsym $mod+$left focus left\n"
									  "#This is the second comment\t\t\t\n"
									  "bindsym $mod+$down focus down\n"
									  "\t\t\t#This is the third comment\n"
									  "bindsym $mod+$up focus up\n"
									  "\t    #this is the fourth comment\n"
									  "bindsym $mod+$right focus right");

		WHEN("Scanning the data")
		{
			auto const lines = i3s::parsing::scan_data(data);

			THEN("The scanning should return 4 lines") { CHECK(lines.size() == 4); }
		}
	}
}

SCENARIO("Scanning empty lines", "[parsing][scanning]")
{
	GIVEN("0 lines of valid data & 2 empty lines")
	{
		auto const data = std::string("\n\n");

		WHEN("Scanning the data")
		{
			auto const lines = i3s::parsing::scan_data(data);

			THEN("The scanning should return 0 lines") { CHECK(lines.size() == 0); }
		}
	}
}

SCENARIO("Scanning empty data", "[parsing][scanning]")
{
	GIVEN("No data")
	{
		auto const data = std::string();

		WHEN("Scanning the data")
		{
			const auto lines = i3s::parsing::scan_data(data);

			THEN("There should be no lines") { CHECK(lines.empty()); }
		}
	}
}
