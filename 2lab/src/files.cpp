#include <files.hpp>
#include <fstream>
#include <sstream>

int string_to_file(const std::string &filename, const std::string &str) {
  std::ofstream file(filename);
  if (file) {
    file << str;
    return 0;
  }
  return 1;
}

std::string file_to_string(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (file) {
    std::ostringstream os;
    os << file.rdbuf();
    return std::string(os.str());
  }
  return std::string();
}

int generate_file_with_random_tasks(const std::string &filename, size_t max_r,
                                    size_t max_t, size_t n) {
  return string_to_file(filename, task_list_to_string(generate_random_task_list(
                                      max_r, max_t, n)));
}
