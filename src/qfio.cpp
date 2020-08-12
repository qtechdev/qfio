#include <fstream>
// #include <iostream>

#include "qfio.hpp"

std::optional<std::string> qfio::read(const std::filesystem::path &p) {
  std::ifstream ifs(p);

  if (ifs) {
    ifs.seekg(0, std::ios::end);
    std::size_t filesize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::string data;
    data.resize(filesize);
    ifs.read(&data[0], filesize);

    return data;
  }

  return {};
}

std::optional<std::vector<uint8_t>> qfio::readb(const std::filesystem::path &p) {
  std::ifstream ifs(p, std::ios::binary);

  if (ifs) {
    // ifs.seekg(0, std::ios::end);
    // std::size_t filesize = ifs.tellg();
    // ifs.seekg(0, std::ios::beg);

    std::vector<uint8_t> data(
      (std::istreambuf_iterator<char>(ifs)),
      std::istreambuf_iterator<char>()
    );

    return data;
  }

  return {};
}

bool qfio::write(
  const std::filesystem::path &p, const std::string &data, const bool trunc
) {
  std::ofstream ofs;

  if (trunc) {
    ofs.open(p, std::ios::out | std::ios::trunc);
  } else {
    ofs.open(p, std::ios::out | std::ios::app);
  }

  if (ofs) {
    ofs.write(data.c_str(), data.size());

    return true;
  }

  return false;
}

bool qfio::write(
  const std::filesystem::path &p, const std::vector<uint8_t> &data,
  const bool trunc
) {
  std::ofstream ofs;

  if (trunc) {
    ofs.open(p, std::ios::out | std::ios::trunc);
  } else {
    ofs.open(p, std::ios::out | std::ios::app);
  }

  if (ofs) {
    ofs.write(reinterpret_cast<const char *>(data.data()), data.size());

    return true;
  }

  return false;
}

std::vector<std::filesystem::path> qfio::get_files_in_directory(
  const std::filesystem::path &directory) {
  std::vector<std::filesystem::path> files;

  if (std::filesystem::is_directory(directory)) {
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
      if (std::filesystem::is_regular_file(entry.path())) {
        files.push_back(entry.path());
      } else if (std::filesystem::is_directory(entry.path())){
        for (const auto &file : get_files_in_directory(entry.path())) {
          files.push_back(file);
        }
      }
    }
  }

  return files;
}
