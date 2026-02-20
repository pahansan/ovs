#include "files.hpp"
#include "schedule.hpp"
#include "task.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <dir> <elementary machines count>\n";
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
                             "_x_" + std::to_string(em_count) + ".txt"));
    task_set_size += 500;
  } while (task_sets.back().size() > 0);

  if (task_sets.size() == 0) {
    std::cerr << "Error: can't open any file\n";
    return 1;
  }
  task_sets.pop_back();

  Schedule sched(em_count);
  std::vector<double> nfdh_errors;
  std::vector<double> ffdh_errors;

  for (const auto &tasks : task_sets) {
    sched.AddTasksNFDH(tasks);
    nfdh_errors.push_back(sched.error());
    sched.AddTasksFFDH(tasks);
    ffdh_errors.push_back(sched.error());
  }

  double nfdh_average = 0.0;
  double ffdh_average = 0.0;
  for (size_t i = 0; i < task_sets.size(); i++) {
    nfdh_average += nfdh_errors[i];
    ffdh_average += ffdh_errors[i];
  }
  nfdh_average /= task_sets.size();
  ffdh_average /= task_sets.size();
  double nfdh_s = 0.0;
  double ffdh_s = 0.0;
  for (size_t i = 0; i < task_sets.size(); i++) {
    nfdh_s += (nfdh_errors[i] - nfdh_average) * (nfdh_errors[i] - nfdh_average);
    ffdh_s += (ffdh_errors[i] - ffdh_average) * (ffdh_errors[i] - ffdh_average);
  }

  std::cout << std::string(45, '-') << "\n";
  std::cout << std::left << std::setw(15) << "Algorithm"
            << "|" << std::setw(13) << " Avg"
            << "|" << std::setw(12) << " MSE" << " |\n";
  std::cout << std::string(45, '-') << "\n";

  std::cout << std::left << std::setw(15) << "NFDH"
            << "|" << ' ' << std::left << std::fixed << std::setprecision(6)
            << std::setw(11) << nfdh_average << " "
            << "|" << ' ' << std::left << std::fixed << std::setprecision(6)
            << std::setw(11) << nfdh_s << " |\n";

  std::cout << std::left << std::setw(15) << "FFDH"
            << "|" << ' ' << std::left << std::fixed << std::setprecision(6)
            << std::setw(11) << ffdh_average << " "
            << "|" << ' ' << std::left << std::fixed << std::setprecision(6)
            << std::setw(11) << ffdh_s << " |\n";

  std::cout << std::string(45, '-') << "\n";
}
