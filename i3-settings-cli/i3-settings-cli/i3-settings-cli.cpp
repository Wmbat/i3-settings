#include <libi3-settings/settings.hpp>

auto main() -> int
{
	if (auto res = i3s::load_config_data("~/.config/i3/config").transform(i3s::extract_settings))
	{
	}
}
