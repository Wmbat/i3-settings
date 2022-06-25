#include <libi3-settings/settings.hpp>

#include <libi3-settings/defines.hpp>
#include <libi3-settings/parsing/lexing.hpp>

#include <range/v3/view/split.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/trim.hpp>

#include <fmt/ranges.h>

#include <fstream>
#include <system_error>

namespace
{
	namespace rv = ranges::views;

	auto to_string_view(ranges::detail::split_outer_iterator<
						ranges::split_view<std::basic_string_view<char>, ranges::single_view<char>>,
						true>::value_type line) -> std::string_view
	{
		return {&*line.begin(), std::size_t(ranges::distance(line))};
	}

	auto is_comment(std::string_view line) -> bool
	{
		auto spaces = line | rv::take_while([](char c) {
						  return std::isspace(c);
					  });
		auto spaces_offset = std::size_t(ranges::distance(spaces));

		return line[spaces_offset] == '#';
	}
	auto is_empty(std::string_view line) -> bool { return line.empty(); }

	/**
	 * TODO(wmbat): Make unicode friendly
	 */
	auto is_space(char c) -> bool { return std::isspace(c); }

	auto trim_line(std::string_view const line)
	{
		return line | rv::trim(is_space);
	}
} // namespace

namespace i3s
{
	auto make_error_code(parse_error error_code) -> std::error_code
	{
		return std::error_code({static_cast<int>(error_code), detail::parse_error_category{}});
	}

	auto extract_settings(std::string&& data) -> tl::expected<settings, error>
	{
		// clang-format off

		auto const scanned_data = std::string_view(data) // ┐ 
			| rv::split('\n')                            // │ 
			| rv::transform(to_string_view)              // │ This code performs the "scanning" phase 
			| rv::remove_if(is_empty)                    // │ of the lexical analysis & removes all 
			| rv::remove_if(is_comment)                  // │ unnecessary components of the text 
			| rv::transform(trim_line)                   // │ such as comments, empty lines, etc...
			| rv::join                                   // │
			| ranges::to<std::string>;                   // ┘

		// clang-format on

		auto const tokens = parsing::lex(scanned_data);

		fmt::print("{}", tokens);

		return {};
	}
} // namespace i3s
