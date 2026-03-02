#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>
class PaymentMatrix {
  size_t rows_, cols_;
  std::vector<double> matrix;

public:
  PaymentMatrix(size_t n, double c1, double c2, double c3)
      : rows_(n + 1), cols_(n + 1), matrix(std::vector<double>(rows_ * cols_)) {
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
};

int main() {
  PaymentMatrix m(10, 1, 2, 3);
  std::cout << m;
}
