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
		keyword,
		identifier,
		command,
		keysym,

		integer_literal,
		string_literal,

		binary_operator,

		unknown
	};

	/**
	 * @brief Models the concept of a token for helping in the lexical analysis
	 *
	 * The token class contains a lexeme (the text that was parsed from the file) and it's
	 * corresponding type, indicating what kind of lexeme we are dealing with
	 */
	struct token
	{
		std::string lexeme; ///< The lexeme of the token
		token_type type;	///< The type of the token
	};
} // namespace i3s::parsing

template <>
struct fmt::formatter<i3s::parsing::token_type>
{
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

	template <class FormatContext>
	constexpr auto format(i3s::parsing::token_type val, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", magic_enum::enum_name(val));
	}
};

template <>
struct fmt::formatter<i3s::parsing::token>
{
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

	template <class FormatContext>
	constexpr auto format(const i3s::parsing::token& val, FormatContext& ctx)
	{
		return format_to(ctx.out(), "token = {{.lexeme = {}, .type = {}}}", val.lexeme, val.type);
	}
};
