#include <libi3-settings/settings.hpp>
#include <libi3-settings/utils/file-io.hpp>

auto main() -> int
{
	if (auto res = i3s::load_file("/home/wmbat/.config/i3"))
	{}
	else
	{
		fmt::print("{:s}", res.error());
	}

	return 0;
}
