#include <libi3-settings/utils/file-io.hpp>

#include <libi3-settings/utils/levenshtein-distance.hpp>

#include <range/v3/algorithm/max_element.hpp>

/**
 * standard library
 */

#include <filesystem>
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
	struct file_difference
	{
		std::filesystem::path file;
		std::size_t difference;
	};

	auto load_file(std::filesystem::path const& path) -> tl::expected<std::string, error>
	{
		if (!std::filesystem::exists(path))
		{
			/*
			if (path.has_parent_path())
			{
				std::vector<file_difference> differences;
				for (auto const& it : std::filesystem::directory_iterator{path.parent_path()})
				{
					auto const target = path.filename().string();
					auto const alternative = it.path().filename().string();

					differences.push_back(
						{.file = it.path(),
						 .difference = i3s::levenshtein_distance(target, alternative)});
				}

				auto const it = ranges::max_element(differences, {}, &file_difference::difference);

				if (it != ranges::end(differences))
				{
					return tl::unexpected(
						error(fmt::format("Unable to open the file \"{}\"", path.c_str()),
							  fmt::format("did you mean to open \"{}\"?", it->file.c_str()),
							  make_error_code(load_file_error::failed_to_open_file),
							  I3S_SOURCE_LOCATION));
				}
			}
			*/

			return tl::unexpected(
				error(fmt::format("\"{}\" does not point to an existing file", path.c_str()),
					  make_error_code(load_file_error::file_does_not_exist), I3S_SOURCE_LOCATION));
		}

		if (std::filesystem::is_directory(path))
		{
			return tl::unexpected(error(fmt::format("\"{}\" is not a file", path.c_str()),
										make_error_code(load_file_error::file_does_not_exist),
										I3S_SOURCE_LOCATION));
		}

		auto file = std::fstream(path);
		if (!file.is_open())
		{
			return tl::unexpected(error(fmt::format("Unable to open the file \"{}\"", path.c_str()),
										make_error_code(load_file_error::failed_to_open_file),
										I3S_SOURCE_LOCATION));
		}

		file.seekg(0, std::ios::end);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		auto file_data = std::string(static_cast<std::size_t>(size), char{});

		file.read(file_data.data(), size);

		return file_data;
	}

	auto make_error_code(load_file_error error_code) -> std::error_code
	{
		return std::error_code({static_cast<int>(error_code), load_file_error_cat});
	}
} // namespace i3s
