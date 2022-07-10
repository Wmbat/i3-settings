/**
 * @file libi3-settings/utils/file-io.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

/**
 * local library
 */

#include <libi3-settings/core/error.hpp>

/**
 * third party libraries
 */

#include <magic_enum.hpp>

#include <tl/expected.hpp>

/**
 * standard library
 */

#include <filesystem>

namespace i3s
{
	/**
	 * @brief The types of errors that may occur when reading a file
	 */
	enum struct load_file_error
	{
		file_does_not_exist, ///< Indicates that the file does not exist on the system
		not_a_file,			 ///< Indicates that the path does not point to a file
		failed_to_open_file, ///< Indicates that the file was unabled to be opened
	};

	/**
	 * @brief Attemps to open & read a file to string
	 *
	 * @param[in] path The filepath to the file
	 */
	auto load_file(std::filesystem::path const& path) -> tl::expected<std::string, error>;

	/**
	 * @brief Turn an enum error into a standard <a
	 * href="https://en.cppreference.com/w/cpp/error/error_code">error_code</a>
	 *
	 * @param[in] error The error value
	 */
	auto make_error_code(load_file_error error) -> std::error_code;
} // namespace i3s
