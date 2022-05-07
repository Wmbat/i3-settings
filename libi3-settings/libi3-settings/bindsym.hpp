#pragma once

#include <libi3-settings/core/keysym.hpp>

#include <string>

namespace i3s
{
	struct bindsym
	{
		keysym keysym;
		std::string command;
	};
} // namespace i3s
