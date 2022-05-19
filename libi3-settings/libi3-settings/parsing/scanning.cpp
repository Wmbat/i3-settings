#include <libi3-settings/parsing/scanning.hpp>

#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/trim.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <ranges>
#include <string>
#include <string_view>

namespace i3s::parsing
{
	namespace rv = ranges::views;

	struct line_adder
	{
		constexpr auto operator()(std::string output, std::string_view line) -> std::string
		{
			output += line;
			output += '\n';
			return output;
		}
	};

	auto is_comment(std::string_view line) -> bool
	{
		auto spaces = line | rv::take_while([](char c) {
						  return std::isspace(c);
					  });
		auto spaces_offset = std::size_t(ranges::distance(spaces));

		return line[spaces_offset] == '#';
	}
	auto is_empty(std::string_view line) -> bool { return line.empty(); }

	auto scan_data(std::string_view data) -> std::vector<std::string_view>
	{
		/*
		 * The call could be removed and the simpler
		 *
		 * auto lines = data
		 *   | rv::split('\n')
		 *   | rv::transform([](auto word){
		 *       return std::string_view(word);
		 *     });
		 *
		 *  could be used with better std::ranges support and C++23
		 */

		// clang-format off

		return data 
			| rv::split('\n') 
			| rv::transform([](auto line) { 
					return std::string_view(&*line.begin(), std::size_t(ranges::distance(line))); 
				})
			| rv::remove_if(is_empty)
			| rv::remove_if(is_comment)
			| ranges::to<std::vector>;

		// clang-format on
	}
} // namespace i3s::parsing
