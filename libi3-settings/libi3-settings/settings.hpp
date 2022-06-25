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

	enum struct parse_error
	{

	};

	namespace detail
	{
		struct parse_error_category : std::error_category
		{
			[[nodiscard]] auto name() const noexcept -> char const* override
			{
				return "i3s::parse_config";
			}

			[[nodiscard]] auto message(int err) const -> std::string override
			{
				return std::string(magic_enum::enum_name(static_cast<i3s::parse_error>(err)));
			}
		};
	} // namespace detail

	auto make_error_code(parse_error error_code) -> std::error_code;

	auto extract_settings(std::string&& data) -> tl::expected<settings, error>;
} // namespace i3s
