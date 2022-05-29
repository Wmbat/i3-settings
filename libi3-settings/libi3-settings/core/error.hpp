#pragma once

#include <libi3-settings/core/source_location.hpp>

#include <fmt/format.h>

#include <system_error>

namespace i3s
{
	struct error
	{
	public:
		error(std::error_code error_code, source_location location);
		error(std::error_code error_code, std::string_view context, source_location location);

		[[nodiscard]] auto what() const noexcept -> std::string_view;

	private:
		std::error_code m_error_code;
		std::string m_what;
	};
} // namespace i3s

template <>
class fmt::formatter<i3s::error>
{
};
