#pragma once

#include <string_view>
#include <vector>

namespace i3s::parsing
{
	auto scan_data(std::string_view data) -> std::vector<std::string_view>;
}
