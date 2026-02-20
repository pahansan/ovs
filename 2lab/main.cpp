#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

struct Task {
  size_t t, r;
  Task(size_t t, size_t r) : t(t), r(r) {}
  std::string to_string() const {
    return std::to_string(t) + " " + std::to_string(r);
  }
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

class TournamentTree {
  std::vector<size_t> tree;
  size_t n_leaves;

public:
  TournamentTree(size_t n_tasks, size_t n_em)
      : n_leaves(std::__bit_ceil(n_tasks)) {
    tree.insert(tree.begin(), n_leaves * 2, n_em);
  }
  int find_first_fit(size_t r) {
    if (tree[1] < r)
      return -1;
    size_t idx = 1;
    while (idx < n_leaves) {
      if (tree[idx * 2] >= r)
        idx *= 2;
      else
        idx = idx * 2 + 1;
    }
    size_t em_idx = idx - n_leaves;
    tree[idx] -= r;
    while (idx > 1) {
      idx /= 2;
      tree[idx] = std::max(tree[idx * 2], tree[idx * 2 + 1]);
    }
    return em_idx;
  }
};

class Schedule {
  std::vector<std::vector<Task>> schedule;
  size_t em_count;

public:
  Schedule(size_t em_count) : em_count(em_count) {}
  int AddTasksNFDH(std::vector<Task> tasks) {
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

  int AddTasksFFDH(std::vector<Task> tasks) {
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

  size_t Time() {
    size_t t = 0;
    for (const auto &layer : schedule) {
      t += layer[0].t;
    }
    return t;
  }

  double error() {
    double T = 0.0;
    for (const auto &layer : schedule)
      for (const auto &task : layer)
        T += task.r * task.t;
    T /= em_count;
    return (Time() - T) / T;
  }

  friend std::ostream &operator<<(std::ostream &os, const Schedule &s) {
    size_t start_time = 0;
    size_t start_em = 1;
    for (const auto &layer : s.schedule) {
      os << "t = " << start_time << "; ";
      for (const auto &task : layer) {
        os << "m = " << start_em << "-" << start_em + task.r - 1 << "; ";
        start_em += task.r;
      }
      os << '\n';
      start_time += layer[0].t;
      start_em = 1;
    }
    return os;
  }
};

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

void string_to_file(const std::string &filename, const std::string &str) {
  std::ofstream file(filename);
  file << str;
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

std::vector<Task> string_to_task_list(const std::string &str) {
  std::stringstream ss(str);
  std::vector<Task> tasks;
  size_t t, r;
  while (ss >> t >> r) {
    tasks.push_back(Task(t, r));
  }
  return tasks;
}

void generate_file_with_random_tasks(const std::string &filename, size_t max_r,
                                     size_t max_t, size_t n) {
  string_to_file(filename, task_list_to_string(
                               generate_random_task_list(max_r, max_t, n)));
}

int main(int argc, char *argv[]) {
  Schedule sched(1024);
  if (sched.AddTasksFFDH(generate_random_task_list(1024, 100, 1000))) {
    std::cerr << "Errrrr....\n";
    return 1;
  }
  std::cout << "Time: " << sched.Time() << '\n';
  std::cout << "Error: " << sched.error() << '\n';
  generate_file_with_random_tasks("fileek", 1024, 100, 10);
  std::vector<Task> tasks = string_to_task_list(file_to_string("fileek"));
  for (const auto &task : tasks)
    std::cout << task.to_string() << '\n';
  // std::cout << sched;
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
