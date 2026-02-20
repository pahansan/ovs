#pragma once

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <vector>

class TournamentTree {
  std::vector<size_t> tree;
  size_t n_leaves;

public:
  TournamentTree(size_t n_tasks, size_t n_em)
      : n_leaves(std::__bit_ceil(n_tasks)) {
    tree.insert(tree.begin(), n_leaves * 2, n_em);
  }
  int find_first_fit(size_t r);
};
