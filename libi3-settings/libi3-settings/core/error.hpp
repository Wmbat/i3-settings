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
		error(std::error_code error_code, std::string const& context, source_location location);
		error(std::error_code error_code, std::string const& context,
			  std::string const& extra_information, source_location location);

		[[nodiscard]] auto what() const noexcept -> std::string_view;

	private:
		std::error_code m_error_code;
		std::string m_what;
	};
} // namespace i3s

/// @private
template <>
struct fmt::formatter<i3s::error>
{
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

	template <class FormatContext>
	constexpr auto format(const i3s::error& val, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", val.what());
	}
};
