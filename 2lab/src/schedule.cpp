#include "schedule.hpp"
#include "tournament_tree.hpp"

int Schedule::AddTasksNFDH(std::vector<Task> tasks) {
  schedule.clear();
  reverse_counting_sort(tasks);
  size_t current_layer = 0;
  size_t free_ems = em_count;
  schedule.push_back(std::vector<Task>());
  for (const auto &task : tasks) {
    if (task.r > em_count)
      return 1;
    if (task.r > free_ems) {
      current_layer++;
      schedule.push_back(std::vector<Task>());
      free_ems = em_count;
    }
    schedule[current_layer].push_back(task);
    free_ems -= task.r;
  }
  return 0;
}

int Schedule::AddTasksFFDH(std::vector<Task> tasks) {
  schedule.clear();
  reverse_counting_sort(tasks);
  TournamentTree tree(tasks.size(), em_count);
  for (const auto &task : tasks) {
    int idx = tree.find_first_fit(task.r);
    if (idx == -1)
      return 1;
    if (idx >= schedule.size())
      schedule.resize(idx + 1);
    schedule[idx].push_back(task);
  }
  return 0;
}

size_t Schedule::Time() {
  size_t t = 0;
  for (const auto &layer : schedule) {
    t += layer[0].t;
  }
  return t;
}

double Schedule::error() {
  double T = 0.0;
  for (const auto &layer : schedule)
    for (const auto &task : layer)
      T += task.r * task.t;
  T /= em_count;
  return (Time() - T) / T;
}
