#include <libi3-settings/core/error.hpp>
#include <string>
#include <utility>

namespace i3s
{
	error::error(std::error_code error_code, source_location location) :
		m_error_code(error_code),
		m_what(fmt::format("Error found at {}:{}: in function {}:\n\terror code: {}",
						   location.file_name(), location.line(), location.function_name(),
						   m_error_code.message()))

	{}
	error::error(std::error_code error_code, std::string_view context, source_location location) :
		m_error_code(error_code),
		m_what(fmt::format(
			"Error found at {}:{}: in function {}:\n\terror code: {}\n\treason for failure: {}",
			location.file_name(), location.line(), location.function_name(), m_error_code.message(),
			context))
	{}

	auto error::what() const noexcept -> std::string_view { return m_what; }

} // namespace i3s
