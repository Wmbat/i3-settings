#pragma once

#include <string_view>
#include <vector>

namespace i3s::parsing
{
	/**
	 * @brief Goes thru data and removes all unnecessary lines & comments
	 *
	 * @param[in] data The raw data to scan
	 *
	 * @returns A vector of lines to further process
	 */
	auto scan_data(std::string_view data) -> std::string;
}
