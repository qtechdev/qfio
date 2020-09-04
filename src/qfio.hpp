#ifndef __FILE_IO_HPP__
#define __FILE_IO_HPP__

#include <cstdint> // std::uint8_t
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace qfio {
  std::optional<std::string> read(const std::filesystem::path &p);
  std::optional<std::vector<std::uint8_t>> readb(const std::filesystem::path &p);
  bool write(
    const std::filesystem::path &p, const std::string &data,
    const bool trunc=false
  );
  bool write(
    const std::filesystem::path &p, const std::vector<std::uint8_t> &data,
    const bool trunc=false
  );

  // equivalent to `find <directory> -type f -maxdepth <maxdepth>
  // set `maxdepth` to -1 for no limit
  std::vector<std::filesystem::path> get_files_in_directory(
    const std::filesystem::path &directory, int maxdepth=1
  );
}

#endif // __FILE_IO_HPP__
