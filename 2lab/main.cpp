#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <vector>

struct Task {
  size_t t, r;
  Task(size_t t, size_t r) : t(t), r(r) {}
  bool operator>(const Task &other) const { return t > other.t; }
  bool operator<(const Task &other) const { return t < other.t; }
  bool operator==(const Task &other) const { return t == other.t; }
};

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

class Schedule {
  std::vector<std::vector<Task>> schedule;
  size_t em_count;

public:
  Schedule(size_t em_count) : em_count(em_count) {}
  int AddTasksNFDH(std::vector<Task> tasks) {
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
  size_t Time() {
    size_t t = 0;
    for (const auto &layer : schedule) {
      t += layer[0].t;
    }
    return t;
  }
  friend std::ostream &operator<<(std::ostream &os, const Schedule &s) {
    size_t start_time = 0;
    size_t start_em = 1;
    for (const auto &layer : s.schedule) {
      for (const auto &task : layer) {
        os << "t = " << start_time << ", m = " << start_em << "-"
           << start_em + task.r - 1 << "; ";
        start_em += task.r;
      }
      os << '\n';
      start_time += layer[0].t;
      start_em = 1;
    }
    return os;
  }
};

int main(int argc, char *argv[]) {
  std::vector<Task> tasks = {Task(2, 1), Task(3, 2), Task(4, 3), Task(6, 1)};
  Schedule sched(5);
  sched.AddTasksNFDH(tasks);
  std::cout << sched.Time() << '\n';
  std::cout << sched;
  // std::vector<float> vec;
  // for (int i = 0; i < std::atoi(argv[1]); i++)
  //   vec.push_back(static_cast<float>(std::rand() % 10));
  // auto start = std::chrono::high_resolution_clock::now();
  // reverse_counting_sort(vec);
  // auto end = std::chrono::high_resolution_clock::now();
  // std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
  // start)
  //                  .count()
  //           << '\n';
}
