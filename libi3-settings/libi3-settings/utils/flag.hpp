#pragma once

#include <libi3-settings/defines.hpp>
#include <libi3-settings/utils/enums.hpp>

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

	template <class Enum>
		requires is_scoped_enum_v<Enum>
	struct flag
	{
	public:
		using enum_type = Enum;
		using underlying_type = std::underlying_type_t<Enum>;

	public:
		constexpr flag() = default;
		constexpr flag(enum_type value) noexcept : m_mask(to_underlying(value)) {}
		constexpr flag(underlying_type value) noexcept : m_mask(value) {}

		constexpr explicit operator underlying_type() const noexcept { return m_mask; }

		constexpr auto operator<=>(flag const& rhs) const = default;

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
