#pragma once

#include <task.hpp>

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <string>

void string_to_file(const std::string &filename, const std::string &str);
std::string file_to_string(const std::string &filename);
void generate_file_with_random_tasks(const std::string &filename, size_t max_r,
                                     size_t max_t, size_t n);
