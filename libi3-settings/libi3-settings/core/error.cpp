#include <libi3-settings/core/error.hpp>
#include <string>
#include <utility>

namespace i3s
{
	error::error(std::error_code error_code, source_location location) :
		m_error_code(error_code),
		m_what(fmt::format("Error found at {}:\n\terror code: {}", location, error_code.message()))

	{}
	error::error(std::error_code error_code, std::string const& context, source_location location) :
		m_error_code(error_code), m_what(fmt::format("Error found at {}: {}\n\terror code: {}",
													 location, context, error_code.message()))
	{}
	error::error(std::error_code error_code, std::string const& context,
				 std::string const& extra_information, source_location location) :
		m_error_code(error_code),
		m_what(fmt::format("Error found at {}: {}\n\terror code: {}\n\textra information: \n\t\t{}",
						   location, context, extra_information, error_code.message()))
	{}

	auto error::what() const noexcept -> std::string_view { return m_what; }

} // namespace i3s
