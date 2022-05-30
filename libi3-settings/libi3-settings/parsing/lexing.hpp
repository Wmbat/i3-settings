/**
 * @file libi3-settings/parsing/lexing.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

/**
 * local library
 */

#include <libi3-settings/parsing/token.hpp>

/**
 * third-party libraries
 */

#include <range/v3/view/adaptor.hpp>
#include <range/v3/view/view.hpp>

/**
 * standard library
 */

#include <span>
#include <vector>

namespace i3s::parsing
{
	auto lex_data(std::string_view const config_data) -> std::vector<token>;

	/**
	 * @brief A view to perform lexical analysis on some input forward range.
	 *
	 * @tparam Range The input forward range
	 */
	template <std::ranges::forward_range Range>
	struct lex_view : public ranges::view_adaptor<lex_view<Range>, Range>
	{
		friend ranges::range_access;

	public:
		lex_view() = default;
		/**
		 * @brief Construct the view by taking in the input range
		 *
		 * @param[in] range The input range to iterate over
		 */
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

	/**
	 * @brief Template type deduction hint for lex_view
	 *
	 * @tparam Range The input forward range
	 */
	template <std::ranges::forward_range Range>
	lex_view(Range&&) -> lex_view<ranges::views::all_t<Range>>;

	namespace views
	{
		/**
		 * @brief Base functor used to enable the piping of the lex view with other ranges
		 */
		struct lex_base_fn
		{
			template <std::ranges::forward_range Range>
			constexpr auto operator()(Range&& range) const -> lex_view<ranges::views::all_t<Range>>
			{
				return {ranges::views::all(std::forward<Range>(range))};
			}
		};

		/**
		 * @brief Functor used to enable the piping of the lex view with other ranges
		 */
		struct lex_fn : lex_base_fn
		{
			using lex_base_fn::operator();

			constexpr auto operator()() const { return ranges::make_view_closure(lex_base_fn{}); }
		};

		/**
		 * @brief Closure variable to use for using a lex view in pipe operations.
		 *
		 * Example:
		 * @code
		 * auto const data = read_file("my_file.txt");
		 * auto const lexed_data = data | parsing::views::lex;
		 * @endcode
		 */
		inline constexpr ranges::views::view_closure<lex_fn> lex;
	} // namespace views
} // namespace i3s::parsing
