#pragma once

#include <libi3-settings/core/keysym.hpp>
#include <libi3-settings/core/modifiers.hpp>

#include <string>

namespace i3s
{
	struct bindsym
	{
		modifier_flag modifiers;
		keysym keysym;
		std::string command;
	};
} // namespace i3s
