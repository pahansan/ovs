#pragma once

#include "task.hpp"

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <string>

int string_to_file(const std::string &filename, const std::string &str);
std::string file_to_string(const std::string &filename);
int generate_file_with_random_tasks(const std::string &filename, size_t max_r,
                                    size_t max_t, size_t n);
std::vector<Task> read_tasks_from_file(const std::string &filename);
