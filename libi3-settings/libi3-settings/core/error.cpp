#include <libi3-settings/core/error.hpp>

#include <string>
#include <utility>

namespace i3s
{
	error::error(std::error_code error_code, source_location location) :
		m_error_code(error_code), m_location(location)
	{}
	error::error(std::string cause, std::error_code error_code, source_location location) :
		m_cause(std::move(cause)), m_error_code(error_code), m_location(location)
	{}
	error::error(std::string cause, std::string hint, std::error_code error_code,
				 source_location location) :
		m_cause(std::move(cause)),
		m_hint(std::move(hint)), m_error_code(error_code), m_location(location)
	{}

	[[nodiscard]] auto error::code() const noexcept -> std::error_code { return m_error_code; }
	[[nodiscard]] auto error::cause() const noexcept -> std::string_view { return m_cause; }
	[[nodiscard]] auto error::hint() const noexcept -> std::string_view { return m_hint; }
	[[nodiscard]] auto error::location() const noexcept -> source_location { return m_location; }

} // namespace i3s
