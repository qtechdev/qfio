#include <iostream>

#include "qfio.hpp"

int main() {
  const auto tmp_dir = std::filesystem::temp_directory_path();
  const auto tmp_file = tmp_dir / "qfio_rw.tmp";
  std::cout << "[ info ] temporary directory == " << tmp_dir << "\n";

  const std::string data = "[ pass ] data written and read successfully!";
  if (!qfio::write(tmp_file, data, true)) {
    std::cerr << "[ fail ] write failed\n";
    return 1;
  }

  const auto raw_data = qfio::read(tmp_file);

  if (raw_data) {
    std::cout << *raw_data << "\n";
    return 0;
  }

  std::cerr << "[ fail ] read failed\n";
  return 2;
}
