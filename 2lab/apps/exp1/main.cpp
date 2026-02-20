#include "exp_data.hpp"
#include "files.hpp"
#include "schedule.hpp"
#include "task.hpp"
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <dir> <elementary machines count> <NFDH/FFDH>\n";
    return 1;
  }
  size_t em_count = std::atoi(argv[2]);
  if (em_count < 1) {
    std::cerr << "Error: elementary machines count\n";
    return 1;
  }
  std::string dir(argv[1]);
  if (dir[dir.length() - 1] != '/')
    dir += "/";
  std::vector<std::vector<Task>> task_sets;
  size_t task_set_size = 500;

  do {
    task_sets.push_back(
        read_tasks_from_file(dir + "tasks_" + std::to_string(task_set_size) +
                             "_100_" + std::to_string(em_count) + ".txt"));
    task_set_size += 500;
  } while (task_sets.back().size() > 0);

  if (task_sets.size() == 0) {
    std::cerr << "Error: can't open any file\n";
    return 1;
  }
  task_sets.pop_back();

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

  for (const auto &tasks : task_sets) {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NRUNS; i++) {
      if (type == NFDH)
        sched.AddTasksNFDH(tasks);
      else
        sched.AddTasksFFDH(tasks);
    }
    auto end = std::chrono::high_resolution_clock::now();
    size_t duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    double duration_in_seconds =
        static_cast<double>(duration) / 1000000000.0 / NRUNS;
    std::cout << std::setw(6) << std::left << tasks.size() << std::fixed
              << std::setprecision(9) << duration_in_seconds << '\n';
  }
}
