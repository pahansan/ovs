#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

class PaymentMatrix {
  size_t rows_, cols_;
  std::vector<double> matrix;

public:
  struct Solution {
    std::vector<double> X, Y, P, PE;
    size_t n_iter = 0;
    Solution(size_t n) : X(n + 1, 0), Y(n + 1, 0), P(n + 1, 0), PE(n + 1, 0) {}
    void add_row(const PaymentMatrix &C, size_t i) {
      P[i]++;
      for (size_t j = 0; j < X.size(); j++)
        Y[j] += C.elem(i, j);
    }
    void add_col(const PaymentMatrix &C, size_t j) {
      PE[j]++;
      for (size_t i = 0; i < X.size(); i++)
        X[i] += C.elem(i, j);
    }
    void add_iter() { n_iter++; }
    size_t i() {
      return std::distance(X.begin(), std::max_element(X.begin(), X.end()));
    }
    size_t j() {
      return std::distance(Y.begin(), std::min_element(Y.begin(), Y.end()));
    }
    void normalize(size_t n) {
      for (int i = 0; i < X.size(); i++) {
        P[i] /= n;
        PE[i] /= n;
      }
    }
    double cost() {
      return (*std::max_element(X.begin(), X.end()) -
              *std::min_element(Y.begin(), Y.end())) /
             (n_iter * 2);
    }
  };

  PaymentMatrix(size_t n, double c1, double c2, double c3)
      : rows_(n + 1), cols_(n + 1), matrix(rows_ * cols_) {
    for (size_t i = 0; i < rows_; i++)
      for (size_t j = 0; j < cols_; j++)
        if (i >= j)
          elem(i, j) = j * c1 + (i - j) * c2;
        else
          elem(i, j) = i * c2 + (j - i) * c3;
  }
  double &elem(size_t i, size_t j) { return matrix[j + cols_ * i]; }
  const double &elem(size_t i, size_t j) const { return matrix[j + cols_ * i]; }
  size_t rows_count() { return rows_; }
  size_t cols_count() { return cols_; }
  friend std::ostream &operator<<(std::ostream &os, const PaymentMatrix &pm) {
    for (size_t i = 0; i < pm.rows_; i++) {
      for (size_t j = 0; j < pm.cols_; j++) {
        os << std::fixed << std::setprecision(2) << std::setw(6) << std::right
           << pm.elem(i, j);
      }
      os << '\n';
    }
    return os;
  }
  Solution BrownMethod(const double eps) {
    Solution sol = Solution(rows_ - 1);
    do {
      size_t i = sol.i();
      size_t j = sol.j();
      sol.add_row(*this, i);
      sol.add_col(*this, j);
      sol.add_iter();
    } while (sol.cost() * 2 >= eps);
    sol.normalize(sol.n_iter);
    return sol;
  }
};

int main() {
  PaymentMatrix m(10, 1, 2, 3);
  std::cout << "Maтpицa плaтeжeй C:\n";
  std::cout << m;
  double eps = 0.01;
  auto sol = m.BrownMethod(eps);
  std::cout << "Koличecтвo итepaций l = " << sol.n_iter << '\n';
  std::cout << "Цeнa игpы V = " << std::setprecision(3) << sol.cost() << '\n'
            << std::setprecision(2);
  std::cout << "Oптимaльныe cмeшaнныe cтpaтeгии ВЦ:\n";
  for (const auto &elem : sol.P)
    std::cout << elem << ' ';
  std::cout << '\n';
  std::cout << "Oптимaльныe cмeшaнныe cтpaтeгии диcпeтчepa:\n";
  for (const auto &elem : sol.PE)
    std::cout << elem << ' ';
  std::cout << '\n';
}
