#include "tournament_tree.hpp"

#include <algorithm>

int TournamentTree::find_first_fit(size_t r) {
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
