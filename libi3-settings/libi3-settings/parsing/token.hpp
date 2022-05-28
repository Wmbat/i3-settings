#pragma once

#include <magic_enum.hpp>

#include <fmt/core.h>

#include <string>

namespace i3s::parsing
{
	/**
	 *
	 */
	enum struct token_type
	{
		bindsym,
		exec,

		plus,

		identifier,
		command,
		keysym,

		integer_literal,
		string_literal,

		unknown
	};

	struct token
	{
		token_type type;
		std::string lexeme;
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
