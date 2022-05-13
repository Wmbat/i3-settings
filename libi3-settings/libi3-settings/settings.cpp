#include <libi3-settings/settings.hpp>

#include <libi3-settings/defines.hpp>

#include <fstream>
#include <system_error>

namespace
{
	struct load_file_error_category : std::error_category
	{
		[[nodiscard]] auto name() const noexcept -> char const* override
		{
			return "i3s::load_file";
		}

		[[nodiscard]] auto message(int err) const -> std::string override
		{
			return std::string(magic_enum::enum_name(static_cast<i3s::load_file_error>(err)));
		}
	};

	struct parse_error_category : std::error_category
	{
		[[nodiscard]] auto name() const noexcept -> char const* override
		{
			return "i3s::parse_config";
		}

		[[nodiscard]] auto message(int err) const -> std::string override
		{
			return std::string(magic_enum::enum_name(static_cast<i3s::parse_error>(err)));
		}
	};
} // namespace

namespace i3s
{
	auto make_error_code(load_file_error error_code) -> std::error_code
	{
		return std::error_code({static_cast<int>(error_code), load_file_error_category()});
	}
	auto make_error_code(parse_error error_code) -> std::error_code
	{
		return std::error_code({static_cast<int>(error_code), parse_error_category()});
	}

	auto load_config_data(std::filesystem::path const& path)
		-> tl::expected<std::vector<char>, error>
	{
		auto file = std::fstream(path);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);

			auto file_data = std::vector<char>(static_cast<std::size_t>(size));

			file.read(file_data.data(), size);

			return file_data;
		}
		else
		{
			return tl::unexpected(error(make_error_code(load_file_error::failed_to_open_file), {}));
		}
	}

	auto parse_config_data(std::span<const char>) -> tl::expected<settings, error> { return {}; }
} // namespace i3s
