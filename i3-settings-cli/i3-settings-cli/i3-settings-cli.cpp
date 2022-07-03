#include <libi3-settings/utils/file-io.hpp>
#include <libi3-settings/settings.hpp>

auto main() -> int
{
	if (auto res = i3s::load_file("~/.config/i3/confg"))
	{
	}
	else
	{
		fmt::print("{}", res.error());
	}

	return 0;
}
