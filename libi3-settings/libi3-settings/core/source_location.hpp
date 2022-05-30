/**
 * @file libi3-settings/core/source_location.hpp
 * @author wmbat-dev@protonmail.com
 * @brief 
 */

#pragma once

/**
 * standard library
 */

#include <cstddef>

namespace i3s
{
	/**
	 * @brief Represents information about the source code, such as file names, lines numbers, and
	 * function names
	 */
	class source_location
	{
	public:
		/**
		 * @brief Construct a source location capturing the file name, line number & function name
		 * of its call site
		 */
		constexpr source_location(char const* file = __builtin_FILE(), // NOLINT
								  char const* function = __builtin_FUNCTION(),
								  std::size_t line = __builtin_LINE()) :
			m_file_name(file),
			m_function_name(function), m_line(line)
		{}

		/**
		 * @brief The line number of the source_location
		 */
		constexpr auto line() -> std::size_t { return m_line; }
		/**
		 * @brief the file name of the source_location
		 */
		constexpr auto file_name() -> char const* { return m_file_name; }
		/**
		 * @brief the function name of the source_location
		 */
		constexpr auto function_name() -> char const* { return m_function_name; }

	private:
		char const* const m_file_name = nullptr;
		char const* const m_function_name = nullptr;
		std::size_t const m_line = 0;
	};
} // namespace i3s
