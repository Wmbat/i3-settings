#pragma once

#include <string>

namespace i3s
{
	template <class Enum>
		requires is_scoped_enum_v<Enum>
	struct flag
	{
		using enum_type = Enum;
		using underlying_type = typename std::underlying_type_t<Enum>;

	public:
		constexpr flag() = default;
		constexpr flag(enum_type value) noexcept : m_mask(to_underlying(value)) {}

		constexpr auto operator<=>(flag const& rhs) const = default;

		constexpr auto operator|(flag const& rhs) const noexcept -> flag
		{
			return flag(m_mask | rhs.m_mask);
		}

	private:
		underlying_type m_mask = {}
	};
} // namespace i3s
