#include <libi3-settings/parsing/lexing.hpp>

#include <ctre.hpp>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/adaptor.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/trim.hpp>

namespace i3s::parsing
{
	namespace rv = ranges::views;

	[[maybe_unused]] static constexpr auto identifier_pattern =
		ctll::fixed_string{R"(^\$[a-zA-z]+$)"};
	[[maybe_unused]] static constexpr auto string_pattern = ctll::fixed_string{"\"(.*?)\""};

	/**
	 * TODO(wmbat): Make unicode friendly
	 */
	auto is_space(char c) -> bool { return std::isspace(c); }

	auto match_lexemes(std::string_view const line) -> std::vector<token>
	{
		auto tokens = std::vector<token>();

		if (auto res = ctre::match<"^byndsim ">(line))
		{
			
		}

		return {};
	}

	auto trim_line(std::string_view const line) { return line | rv::trim(is_space); }

	auto lex_data(std::string_view const config_data) -> std::vector<token>
	{
		// clang-format off

		/*
		auto const nested_tokens = lines 
			| rv::transform(trim_line)
			| ranges::to<std::vector>;

		return nested_tokens 
			| rv::join 
			| ranges::to<std::vector>;
		*/

		// clang-format on
	}
} // namespace i3s::parsing
