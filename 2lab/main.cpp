#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

template <typename T> void reverse_counting_sort(std::vector<T> &array) {
  std::map<T, size_t, std::greater<T>> count;
  for (const auto &elem : array) {
    count[elem]++;
  }
  size_t offset = 0;
  auto begin = array.begin();
  for (const auto &[value, amount] : count) {
    std::fill_n(begin + offset, amount, value);
    offset += amount;
  }
}

int main(int argc, char *argv[]) {
  std::vector<float> vec;
  for (int i = 0; i < std::atoi(argv[1]); i++)
    vec.push_back(static_cast<float>(std::rand() % 10));
  auto start = std::chrono::high_resolution_clock::now();
  reverse_counting_sort(vec);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count()
            << '\n';
}
