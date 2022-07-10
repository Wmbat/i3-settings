/**
 * @file libi3-settings/core/error.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

/**
 * local library
 */

#include <libi3-settings/core/source_location.hpp>

/**
 * third party libraries
 */

#include <fmt/format.h>

/**
 * standard library
 */

#include <optional>
#include <system_error>

namespace i3s
{
	/**
	 * @brief Represents an common error that may happen during the runtime of the application
	 *
	 * For the error type, the **cause** represents the "why" the error happened & the **hint**
	 * represents the "how to fix it"
	 */
	struct error
	{
	public:
		error(std::error_code error_code, source_location location);
		error(std::string cause, std::error_code code, source_location location);
		error(std::string cause, std::string hint, std::error_code code, source_location location);

		/**
		 * @brief Access the underlying <a
		 * href="https://en.cppreference.com/w/cpp/error/error_code">error_code</a>
		 */
		[[nodiscard]] auto code() const noexcept -> std::error_code;
		/**
		 * @brief Access a string explaining why the error happened
		 */
		[[nodiscard]] auto cause() const noexcept -> std::string_view;
		/**
		 * @brief Access a string giving hints on how to fix the error
		 */
		[[nodiscard]] auto hint() const noexcept -> std::string_view;
		/**
		 * @brief Access the location (in the code) where the error occured
		 */
		[[nodiscard]] auto location() const noexcept -> source_location;

	private:
		std::string m_cause = {};
		std::string m_hint = {};
		std::error_code m_error_code;
		source_location m_location;
	};
} // namespace i3s

/// @private
template <>
struct fmt::formatter<i3s::error>
{
	char presentation = 'l';

	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
	{
		auto it = ctx.begin();
		auto end = ctx.end();

		if (it != end && (*it == 'l' || *it == 's'))
		{
			presentation = *it++;
		}

		if (it != end && *it != '}')
		{
			throw format_error("invalid format");
		}

		return it;
	}

	template <class FormatContext>
	constexpr auto format(const i3s::error& val, FormatContext& ctx)
	{
		if (!val.cause().empty())
		{
			if (!val.hint().empty())
			{
				return presentation == 's'
						   ? format_to(ctx.out(), "error found!\n\tcause: {}\n\thint: {}",
									   val.cause(), val.hint().data())
						   : format_to(
							   ctx.out(), "error found at {}\n\tcause: {}\n\thint: {}\n\tcode: {}",
							   val.location(), val.cause(), val.hint(), val.code().message());
			}
			else
			{
				return presentation == 's'
						   ? format_to(ctx.out(), "error found!\n\tcause: {}", val.cause())
						   : format_to(ctx.out(), "error found at {}\n\tcause: {}\n\tcode: {}",
									   val.location(), val.cause(), val.code().message());
			}
		}
		else
		{
			return presentation == 's'
					   ? format_to(ctx.out(), "error found!\n\tcode: {}", val.code().message())
					   : format_to(ctx.out(), "error found at {}\n\tcode: {}", val.location(),
								   val.code().message());
		}
	}
};
