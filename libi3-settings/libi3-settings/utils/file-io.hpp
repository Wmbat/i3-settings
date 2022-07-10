/**
 * @file libi3-settings/core/file-io.hpp
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
	 *
	 */
	enum struct load_file_error
	{
		file_does_not_exist = 0,
		not_a_file,
		failed_to_open_file,
	};

	/**
	 * @brief
	 */
	auto load_file(std::filesystem::path const& path) -> tl::expected<std::string, error>;

	/**
	 * @brief
	 */
	auto make_error_code(load_file_error error_code) -> std::error_code;
} // namespace i3s
