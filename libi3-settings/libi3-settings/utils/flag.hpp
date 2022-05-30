/**
 * @file libi3-settings/utils/flag.hpp
 * @author wmbat-dev@protonmail.com
 * @brief
 */

#pragma once

/**
 * local library
 */

#include <libi3-settings/defines.hpp>
#include <libi3-settings/utils/enums.hpp>

/**
 * standard library
 */

#include <string>

namespace i3s
{
	template <typename Enum>
		requires is_scoped_enum_v<Enum>
	struct flag_traits
	{
		enum struct traits : std::underlying_type_t<Enum>
		{
			all_bits = 0
		};

		using enum traits;
	};

	/**
	 * @brief Enables flag operations on an specific enum type
	 *
	 * @tparam Enum
	 */
	template <class Enum>
		requires is_scoped_enum_v<Enum>
	struct flag
	{
	public:
		/**
		 * @brief The scoped enumeration type
		 */
		using enum_type = Enum;
		/**
		 * @brief the underlying type of the scoped enumeration
		 */
		using underlying_type = std::underlying_type_t<Enum>;

	public:
		/**
		 * @brief Construct a bit flag with the default value of 0
		 */
		constexpr flag() = default;
		/**
		 * @brief Construct a bit flag from an enum_type value
		 *
		 * @param[in] value The enum value
		 */
		constexpr flag(enum_type value) noexcept : m_mask(to_underlying(value)) {}
		/**
		 * @brief Construct a bit flag from an underlying_type value
		 *
		 * @param[in] value The value
		 */
		constexpr flag(underlying_type value) noexcept : m_mask(value) {}

		/**
		 * @brief Explicit conversion to the underlying_type
		 */
		constexpr explicit operator underlying_type() const noexcept { return m_mask; }

		constexpr auto operator<=>(flag const& rhs) const = default;
		constexpr auto operator==(flag const& rhs) const -> bool = default;

		constexpr auto operator&(flag const& rhs) const noexcept -> flag
		{
			return flag(m_mask & rhs.m_mask);
		}
		constexpr friend auto operator&(flag const& lhs, Enum rhs) noexcept -> flag
		{
			return flag(lhs.m_mask & to_underlying(rhs));
		}
		constexpr auto operator|(flag const& rhs) const noexcept -> flag
		{
			return flag(m_mask | rhs.m_mask);
		}
		constexpr friend auto operator|(flag const& lhs, Enum rhs) noexcept -> flag
		{
			return flag(lhs.m_mask | to_underlying(rhs));
		}
		constexpr auto operator^(flag const& rhs) const noexcept -> flag
		{
			return flag(m_mask ^ rhs.m_mask);
		}
		constexpr friend auto operator^(flag const& lhs, Enum rhs) noexcept -> flag
		{
			return flag(lhs.m_mask | to_underlying(rhs));
		}
		constexpr auto operator~() const noexcept -> flag
		{
			I3S_LET temp = to_underlying(flag_traits<Enum>::all_bits);
			return flag(m_mask ^ temp);
		}

		constexpr auto operator&=(flag const& rhs) noexcept -> flag&
		{
			m_mask &= rhs.m_mask;
			return *this;
		}
		constexpr auto operator|=(flag const& rhs) noexcept -> flag&
		{
			m_mask |= rhs.m_mask;
			return *this;
		}
		constexpr auto operator^=(flag const& rhs) noexcept -> flag&
		{
			m_mask ^= rhs.m_mask;
			return *this;
		}

	private:
		underlying_type m_mask = {};
	};

// NOLINTNEXTLINE
#define I3S_DEFINE_EXTRA_ENUM_OPERATORS(flag)                                                      \
	constexpr auto operator|(flag::enum_type bit0, flag::enum_type bit1) noexcept->flag            \
	{                                                                                              \
		return flag(bit0) | bit1;                                                                  \
	}                                                                                              \
	constexpr auto operator&(flag::enum_type bit0, flag::enum_type bit1) noexcept->flag            \
	{                                                                                              \
		return flag(bit0) & bit1;                                                                  \
	}                                                                                              \
	constexpr auto operator~(flag::enum_type bits) noexcept->flag { return ~(flag(bits)); }

} // namespace i3s
