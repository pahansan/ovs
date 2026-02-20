#include <cstddef>
#include <cstdlib>
#include <files.hpp>

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
              << " <dir> <tasks count> <max time> <max elementary machines>\n";
    return 1;
  }
  size_t tasks_count = std::atoi(argv[2]);
  if (tasks_count < 1) {
    std::cerr << "Error: bad tasks count\n";
    return 1;
  }
  size_t max_time = std::atoi(argv[3]);
  if (max_time < 1) {
    std::cerr << "Error: bad max time\n";
    return 1;
  }
  size_t max_em = std::atoi(argv[4]);
  if (max_em < 1) {
    std::cerr << "Error: bad max elementary machines\n";
    return 1;
  }
  std::string dir(argv[1]);
  if (dir[dir.length() - 1] != '/')
    dir += "/";
  const std::string filename = dir + "tasks_" + std::string(argv[2]) + "_" +
                               std::string(argv[3]) + "_" +
                               std::string(argv[4]) + ".txt";
  if (generate_file_with_random_tasks(filename, max_em, max_time,
                                      tasks_count)) {
    std::cerr << "Error: can't create file with path '" << filename << "'\n";
    return 1;
  }
  std::cout << "Write " << tasks_count << " tasks to '" << filename << "'\n";
}
