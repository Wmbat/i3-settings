/**
 * @file libi3-settings/core/modifiers.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

/**
 * local library
 */

#include <libi3-settings/utils/flag.hpp>

/**
 * third-party libraries
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>

#include <magic_enum.hpp>

/**
 * standard library
 */

#include <string_view>
#include <vector>

namespace i3s
{
	/**
	 * @brief
	 */
	enum struct modifier : std::uint8_t
	{
		mod1 = 1 << 0,
		mod2 = 1 << 1,
		mod3 = 1 << 2,
		mod4 = 1 << 3,
		mod5 = 1 << 4,
		shift = 1 << 5,
		ctrl = 1 << 6
	};

	using modifier_flag = flag<modifier>;

	template <>
	struct flag_traits<modifier>
	{
		enum struct traits : modifier_flag::underlying_type
		{
			all_bits = static_cast<modifier_flag::underlying_type>(
				modifier_flag(modifier::shift) | modifier::ctrl | modifier::mod1 | modifier::mod2
				| modifier::mod3 | modifier::mod4 | modifier::mod5)
		};

		using enum traits;
	};

	I3S_DEFINE_EXTRA_ENUM_OPERATORS(modifier_flag)
} // namespace i3s

/// @private
template <>
struct fmt::formatter<i3s::modifier>
{
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

	template <class FormatContext>
	constexpr auto format(i3s::modifier val, FormatContext& ctx)
	{
		return format_to(ctx.out(), "{}", magic_enum::enum_name(val));
	}
};

/// @private
template <>
struct fmt::formatter<i3s::modifier_flag>
{
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.begin(); }

	template <class FormatContext>
	constexpr auto format(i3s::modifier_flag flag, FormatContext& ctx)
	{
		// clang-format off
		I3S_LET used_enum_values = magic_enum::enum_values<i3s::modifier>()
			| ranges::views::filter([=](i3s::modifier val) { return (flag & val) == val; })
			| ranges::to<std::vector>();
		// clang-format on

		return format_to(ctx.out(), "{}", fmt::format("{}", fmt::join(used_enum_values, "+")));
	}
};
