#include <libi3-settings/core/error.hpp>

#include <magic_enum.hpp>

#include <catch2/catch_test_macros.hpp>

enum struct test_error
{
	error_0,
	error_1,
	error_2,
	error_3
};

struct test_error_category : std::error_category
{
	[[nodiscard]] auto name() const noexcept -> char const* override { return "i3s::load_file"; }

	[[nodiscard]] auto message(int err) const -> std::string override
	{
		return std::string(magic_enum::enum_name(static_cast<test_error>(err)));
	}
};

static const auto test_error_cat = test_error_category();

auto make_error_code(test_error error_code) -> std::error_code
{
	return std::error_code({static_cast<int>(error_code), test_error_cat});
}

auto make_error(std::error_code error_code)
{
	return i3s::error(error_code, {});
}

SCENARIO("")
{
	GIVEN("an simple std::error_code")
	{
		auto const err_code = make_error_code(test_error::error_0);

		WHEN("Creating an i3s::error")
		{
			auto const err = make_error(err_code);

			THEN("") {}
		}
	}
}
