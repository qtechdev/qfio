#include <iostream>

#include "qfio.hpp"

int main() {
  // equivalent to `find . -maxdepth 1 -type f`
  for (const auto &file : qfio::get_files_in_directory(".", 1)) {
    std::cout << file.string() << "\n";
  }

  return 0;
}
