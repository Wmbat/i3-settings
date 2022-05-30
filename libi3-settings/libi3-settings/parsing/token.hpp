/**
 * @file libi3-settings/parsing/token.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */
#pragma once

/**
 * third-party libraries
 */

#include <magic_enum.hpp>

#include <fmt/core.h>

/**
 * standard library
 */

#include <string>

namespace i3s::parsing
{
	/**
	 * @brief The type of each supported token in the lexical analysis of an i3 source file
	 */
	enum struct token_type
	{
		bindsym, ///< represents a bindsym command
		exec,	 ///< represents a exec command

		plus, ///< represents the '+' operator

		identifier,
		command,
		keysym,

		integer_literal,
		string_literal,

		unknown
	};

	/**
	 * @brief Holds the information of a token type and it's corresponding parsed lexeme
	 */
	struct token
	{
		token_type type;	///< The type of the token
		std::string lexeme; ///< The lexeme of the token
	};
} // namespace i3s::parsing

template <>
struct fmt::formatter<i3s::parsing::token_type>
{
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

	template <class FormatContext>
	auto format(i3s::parsing::token_type val, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", magic_enum::enum_name(val));
	}
};
