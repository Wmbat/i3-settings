/**
 * @file libi3-settings/utils/enums.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

/**
 * standard library
 */

#include <type_traits>

namespace i3s
{
	namespace detail
	{
		/// @private
		template <class Type>
		auto test_sizable(int) -> decltype(sizeof(Type), std::true_type{});

		/// @private
		template <class>
		auto test_sizable(...) -> std::false_type;

		/// @private
		template <class Type>
		auto test_nonconvertible_to_int(int)
			-> decltype(static_cast<std::false_type (*)(int)>(nullptr)(std::declval<Type>()));

		/// @private
		template <class>
		auto test_nonconvertible_to_int(...) -> std::true_type;

		/// @private
		template <class Enum>
		constexpr bool is_scoped_enum_impl =
			std::conjunction_v<decltype(test_sizable<Enum>(0)),
							   decltype(test_nonconvertible_to_int<Enum>(0))>;
	} // namespace detail

	/**
	 * @brief Check wether Enum is a scoped enumeration type.
	 *
	 * Provides a member constant value which is equal to **true** if Enum is a scoped enumeration
	 * type. Otherwise, value is equal to **false**
	 *
	 * @tparam Type The type to check
	 */
	template <class Enum>
	struct is_scoped_enum : std::false_type
	{
	};

	/**
	 * @brief Check wether Enum is a scoped enumeration type.
	 *
	 * Provides a member constant value which is equal to **true** if Enum is a scoped enumeration
	 * type. Otherwise, value is equal to **false**
	 *
	 * @tparam Type The type to check
	 */
	template <class Enum>
		requires std::is_enum_v<Enum>
	struct is_scoped_enum<Enum> : std::bool_constant<detail::is_scoped_enum_impl<Enum>>
	{
	};

	template <class Enum>
	constexpr bool is_scoped_enum_v = is_scoped_enum<Enum>::value;

	/**
	 * @brief Cast a scoped enum to its underlying type.
	 *
	 * Equivalent to 
	 * @code
	 * static_cast<std::underlying_type_t<Enum>>(e);
	 * @endcode
	 *
	 * @param[in] e The enum value to cast
	 *
	 * @tparam Enum The enum type
	 */
	template <class Enum>
		requires is_scoped_enum_v<Enum>
	constexpr auto to_underlying(Enum e) noexcept -> std::underlying_type_t<Enum>
	{
		return static_cast<std::underlying_type_t<Enum>>(e);
	}
} // namespace i3s
