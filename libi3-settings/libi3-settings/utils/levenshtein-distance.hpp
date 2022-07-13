/**
 * @file libi3-settings/utils/levenshtein-distance.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

#include <range/v3/view/iota.hpp>

/**
 * standard library
 */

#include <string_view>
#include <vector>

namespace i3s
{
	namespace rv = ranges::views;

	/**
	 * @brief Implements the Levenshtein distance algorithm using Optimal String Alignment. This
	 * algorithm will find how close two ranges are from each others.
	 *
	 * For more information about the algorithm, see <a
	 * href="https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance">here</a>
	 */
	template <std::ranges::random_access_range Range>
	auto levenshtein_distance(Range&& r1, Range&& r2) -> std::size_t
	{
		auto const length_r1 = std::ranges::size(r1);
		auto const length_r2 = std::ranges::size(r2);

		auto distance_matrix = std::vector(length_r1 + 1, std::vector<std::size_t>(length_r2 + 1));

		for (std::size_t i : rv::iota(0u, length_r1 + 1))
		{
			distance_matrix[i][0] = i;
		}

		for (std::size_t j : rv::iota(0u, length_r2 + 1))
		{
			distance_matrix[0][j] = j;
		}

		for (std::size_t i : rv::iota(1u, length_r1 + 1))
		{
			for (std::size_t j : rv::iota(1u, length_r2 + 1))
			{
				std::size_t const cost = r1[i - 1] == r2[j - 1] ? 0u : 1u;

				distance_matrix[i][j] = std::min(
					distance_matrix[i - 1][j] + 1,
					std::min(distance_matrix[i][j - 1] + 1, distance_matrix[i - 1][j - 1] + cost));

				if ((i > 1) && (j > 1) && (r1[i - 1] == r2[j - 2]) && (r1[i - 2] == r2[j - 1]))
				{
					distance_matrix[i][j] =
						std::min(distance_matrix[i][j], distance_matrix[i - 2][j - 2] + 1);
				}
			}
		}

		return distance_matrix[length_r1][length_r1];
	}
} // namespace i3s
