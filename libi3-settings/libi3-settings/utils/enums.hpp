#pragma once

#include <type_traits>

namespace i3s
{
	namespace detail
	{
		template <class Type>
		auto test_sizable(int) -> decltype(sizeof(Type), std::true_type{});

		template <class>
		auto test_sizable(...) -> std::false_type;

		template <class Type>
		auto test_nonconvertible_to_int(int)
			-> decltype(static_cast<std::false_type (*)(int)>(nullptr)(std::declval<Type>()));

		template <class>
		auto test_nonconvertible_to_int(...) -> std::true_type;

		template <class Enum>
		constexpr bool is_scoped_enum_impl =
			std::conjunction_v<decltype(test_sizable<Enum>(0)),
							   decltype(test_nonconvertible_to_int<Enum>(0))>;
	} // namespace detail

	template <class Enum>
	struct is_scoped_enum : std::false_type
	{
	};

	template <class Enum>
		requires std::is_enum_v<Enum>
	struct is_scoped_enum<Enum> : std::bool_constant<detail::is_scoped_enum_impl<Enum>>
	{
	};

	template <class Enum>
	constexpr bool is_scoped_enum_v = is_scoped_enum<Enum>::value;

	template <class Enum>
		requires is_scoped_enum_v<Enum>
	constexpr auto to_underlying(Enum e) noexcept -> std::underlying_type_t<Enum>
	{
		return static_cast<std::underlying_type_t<Enum>>(e);
	}
} // namespace i3s
