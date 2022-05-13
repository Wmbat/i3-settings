#pragma once

#include <libi3-settings/bindsym.hpp>
#include <libi3-settings/core/error.hpp>

#include <tl/expected.hpp>

#include <filesystem>
#include <vector>

namespace i3s
{
	struct settings
	{
		std::vector<bindsym> bindsyms;
	};

	enum struct load_file_error
	{
		failed_to_open_file
	};

	enum struct parse_error
	{

	};

	auto make_error_code(load_file_error error_code) -> std::error_code;
	auto make_error_code(parse_error error_code) -> std::error_code;

	auto load_config_data(std::filesystem::path const& path)
		-> tl::expected<std::vector<char>, error>;

	auto parse_config_data(std::span<const char> config) -> tl::expected<settings, error>;
} // namespace i3s
