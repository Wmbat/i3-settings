#include <libi3-settings/core/file-io.hpp>

/**
 * standard library
 */

#include <fstream>

namespace
{
	/// @private
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

	const static auto load_file_error_cat = load_file_error_category();
} // namespace

namespace i3s
{
	auto load_file(std::filesystem::path const& path) -> tl::expected<std::string, error>
	{
		auto file = std::fstream(path);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			std::streamsize size = file.tellg();
			file.seekg(0, std::ios::beg);

			auto file_data = std::string(static_cast<std::size_t>(size), char{});

			file.read(file_data.data(), size);

			return file_data;
		}
		else
		{
			auto const filename = path.filename();
			auto const parent_path = path.parent_path();

			return tl::unexpected(error(make_error_code(load_file_error::failed_to_open_file),
										fmt::format("Unable to open the file \"{}\"", path.c_str()),
										I3S_SOURCE_LOCATION));
		}
	}

	auto make_error_code(load_file_error error_code) -> std::error_code
	{
		return std::error_code({static_cast<int>(error_code), load_file_error_cat});
	}
} // namespace i3s
