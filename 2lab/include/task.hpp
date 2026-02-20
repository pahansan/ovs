#pragma once

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>

struct Task {
  size_t t, r;
  Task(size_t t, size_t r) : t(t), r(r) {}
  std::string to_string() const;
  bool operator>(const Task &other) const;
  bool operator<(const Task &other) const;
  bool operator==(const Task &other) const;
};

void reverse_counting_sort(std::vector<Task> &array);
Task generate_random_task(std::random_device &gen,
                          std::uniform_int_distribution<size_t> &dist_r,
                          std::uniform_int_distribution<size_t> &dist_t);
std::vector<Task> generate_random_task_list(size_t max_r, size_t max_t,
                                            size_t n);
std::string task_list_to_string(const std::vector<Task> &tasks);
std::vector<Task> string_to_task_list(const std::string &str);
