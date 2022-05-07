#pragma once

#include <libi3-settings/utils/flag.hpp>

namespace i3s
{
	/**
	 * @brief 
	 */
	enum struct modifier : std::uint8_t
	{
		shift,
		lock,
		control,
		mod1,
		mod2,
		mod3,
		mod4,
		mod5
	};
}
