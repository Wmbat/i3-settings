#include <filesystem>
#include <libi3-settings/settings.hpp>
#include <libi3-settings/utils/file-io.hpp>

#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <source_location>

auto create_logger(std::string_view name) -> spdlog::logger;

auto main() -> int
{
	auto logger = create_logger("i3s-cli");

	std::filesystem::path i3_path = "/home/wmbat/.config/i3/config";

	if (auto res = i3s::load_file(i3_path).and_then(i3s::extract_settings))
	{
	}
	else
	{
		fmt::print("{:s}", res.error());
		logger.info("{:l}", res.error());
	}

	return 0;
}

auto create_logger(std::string_view name) -> spdlog::logger
{
	auto const file_sink =
		std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string{name} + ".logs", true);
	file_sink->set_pattern("[%H:%M:%S.%f] [%n] [%^%l%$] %v");
	file_sink->set_level(spdlog::level::trace);

	auto logger = spdlog::logger(std::string(name), {file_sink});
	logger.set_level(spdlog::level::trace);
	return logger;
}
