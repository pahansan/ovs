#include "files.hpp"
#include "schedule.hpp"
#include "task.hpp"

#include <chrono>
#include <iostream>

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
  std::cout << sched;
  std::vector<float> vec;
  for (int i = 0; i < std::atoi(argv[1]); i++)
    vec.push_back(static_cast<float>(std::rand() % 10));
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count()
            << '\n';
}
