#pragma once

#include "task.hpp"

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>

class Schedule {
  std::vector<std::vector<Task>> schedule;
  size_t em_count;

public:
  Schedule(size_t em_count) : em_count(em_count) {}
  int AddTasksNFDH(std::vector<Task> tasks);
  int AddTasksFFDH(std::vector<Task> tasks);
  size_t Time();
  double error();
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
