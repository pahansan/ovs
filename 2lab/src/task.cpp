#include <sstream>
#include <task.hpp>

#include <algorithm>

std::string Task::to_string() const {
  return std::to_string(t) + " " + std::to_string(r);
}
bool Task::operator>(const Task &other) const { return t > other.t; }
bool Task::operator<(const Task &other) const { return t < other.t; }
bool Task::operator==(const Task &other) const { return t == other.t; }

void reverse_counting_sort(std::vector<Task> &array) {
  if (array.empty())
    return;
  Task max_val = *std::max_element(array.begin(), array.end());

  std::vector<std::vector<Task>> count(max_val.t + 1);

  for (const auto &elem : array) {
    count[elem.t].push_back(elem);
  }

  size_t index = 0;
  for (int i = max_val.t; i >= 0; --i) {
    for (const auto &task : count[i]) {
      array[index++] = task;
    }
  }
}

Task generate_random_task(std::random_device &gen,
                          std::uniform_int_distribution<size_t> &dist_r,
                          std::uniform_int_distribution<size_t> &dist_t) {
  return Task(dist_t(gen), dist_r(gen));
}

std::vector<Task> generate_random_task_list(size_t max_r, size_t max_t,
                                            size_t n) {
  if (max_r == 0 || max_t == 0)
    return std::vector<Task>();
  std::random_device gen;
  std::uniform_int_distribution<size_t> dist_r(1, max_r);
  std::uniform_int_distribution<size_t> dist_t(1, max_t);
  std::vector<Task> tasks;
  for (size_t i = 0; i < n; i++) {
    tasks.push_back(generate_random_task(gen, dist_r, dist_t));
  }
  return tasks;
}

std::string task_list_to_string(const std::vector<Task> &tasks) {
  std::string out;
  for (const auto &task : tasks) {
    out += task.to_string() + "\n";
  }
  return out;
}

std::vector<Task> string_to_task_list(const std::string &str) {
  std::stringstream ss(str);
  std::vector<Task> tasks;
  size_t t, r;
  while (ss >> t >> r) {
    tasks.push_back(Task(t, r));
  }
  return tasks;
}
