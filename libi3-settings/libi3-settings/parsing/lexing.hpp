#pragma once

#include "range/v3/view/view.hpp"
#include <libi3-settings/parsing/token.hpp>

#include <range/v3/view/adaptor.hpp>

#include <span>
#include <vector>

namespace i3s::parsing
{
	auto lex_data(std::string_view const config_data) -> std::vector<token>;

	template <std::ranges::forward_range Range>
	struct lex_view : public ranges::view_adaptor<lex_view<Range>, Range>
	{
		friend ranges::range_access;

	public:
		lex_view() = default;
		lex_view(Range&& range) : lex_view::view_adaptor{std::forward<Range>(range)} {}

	private:
		struct adaptor : ranges::adaptor_base
		{
		public:
			adaptor() = default;

			auto read(ranges::iterator_t<Range> it) const { return *it; }

			void next(ranges::iterator_t<Range> it) const { it += 2; };

		private:
		};

		auto begin_adaptor() const -> adaptor { return adaptor{}; }
		auto end_adaptor() const -> adaptor { return adaptor{}; }
	};

	template <class Range>
	lex_view(Range&&) -> lex_view<ranges::views::all_t<Range>>;

	namespace views
	{
		struct lex_base_fn
		{
			template <std::ranges::forward_range Range>
			constexpr auto operator()(Range&& range) const -> lex_view<ranges::views::all_t<Range>>
			{
				return {ranges::views::all(std::forward<Range>(range))};
			}
		};

		struct lex_fn : lex_base_fn
		{
			using lex_base_fn::operator();

			constexpr auto operator()() const { return ranges::make_view_closure(lex_base_fn{}); }
		};

		RANGES_INLINE_VARIABLE(ranges::views::view_closure<lex_fn>, lex);
	} // namespace views
} // namespace i3s::parsing
