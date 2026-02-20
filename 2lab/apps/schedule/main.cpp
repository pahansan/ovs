#include "exp_data.hpp"
#include "files.hpp"
#include "schedule.hpp"
#include "strings.hpp"
#include "task.hpp"
#include <chrono>
#include <cstddef>
#include <cstdlib>

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <filename> <elementary machines count> <NFDH/FFDH>\n";
    return 1;
  }
  size_t em_count = std::atoi(argv[2]);
  if (em_count < 1) {
    std::cerr << "Error: elementary machines count\n";
    return 1;
  }
  const std::string filepath(argv[1]);
  const std::string filename = filepath.substr(filepath.find_last_of("/") + 1);
  const auto params = split(filename, '_');
  if (params.size() < 4) {
    std::cerr << "Error: bad input file name format\n";
    return 1;
  }
  size_t max_em = std::atoi(params[3].c_str());
  if (max_em > em_count) {
    std::cerr << "Error: max elementary machines count greater than elementary "
                 "machines count\n";
    return 1;
  }
  std::vector<Task> tasks = read_tasks_from_file(filename);
  if (tasks.empty()) {
    std::cerr << "Error: can't read file '" << filename << "'\n";
    return 1;
  }
  AlgorithmType type;
  const std::string algorithm_type_str(argv[3]);
  if (algorithm_type_str == "NFDH") {
    type = NFDH;
  } else if (algorithm_type_str == "FFDH") {
    type = FFDH;
  } else {
    std::cerr << "Error: unknown option: " << algorithm_type_str << '\n';
    return 1;
  }
  Schedule sched(em_count);
  auto start = std::chrono::high_resolution_clock::now();
  if (type == NFDH)
    sched.AddTasksNFDH(tasks);
  else
    sched.AddTasksFFDH(tasks);
  auto end = std::chrono::high_resolution_clock::now();
  size_t duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  double duration_in_seconds = static_cast<double>(duration) / 1000000000.0;
  std::cout << "Время выполнения, с: " << duration_in_seconds << '\n';
  std::cout << "T(S), с:             " << sched.Time() << '\n';
  std::cout << "Error:               " << sched.error() << '\n';
  std::cout << "Расписание:\n" << sched;
}
