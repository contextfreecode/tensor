#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

template<typename Val>
using Scalar = Val;

template<typename Val>
using Vec = std::vector<Val>;

template<typename Val>
using Mat = Vec<Vec<Val>>;

template<typename Val>
auto operator<<(std::ostream& out, const Vec<Val>& a) -> std::ostream& {
  for (const auto& x: a | std::ranges::views::take(1)) {
    out << x;
  }
  for (const auto& x: a | std::ranges::views::drop(1)) {
    out << " " << x;
  }
  return out;
}

template<typename Val>
auto operator+(const Vec<Val>& a, const Vec<Val>& b) -> Vec<Val> {
  auto sum = Vec<Val>(a.size());
  std::transform(a.cbegin(), a.cend(), b.cbegin(), sum.begin(),
    [](Val x, Val y) {
      return x + y;
    }
  );
  return sum;
}

template<typename Val>
auto sum_across_cols(const Mat<Val>& matrix) -> Vec<Val> {
  auto sum = Vec<Val>(matrix.size());
  std::transform(matrix.cbegin(), matrix.cend(), sum.begin(),
    [](const Vec<Val>& row) {
      return std::reduce(row.cbegin(), row.cend());
    }
  );
  return sum;
}

template<typename Val>
auto sum_across_rows(const Mat<Val>& matrix) -> Vec<Val> {
  // No control of shape if empty!
  auto m = matrix.empty() ? 0 : matrix[0].size();
  return std::reduce(matrix.cbegin(), matrix.cend(), Vec<Val>(m),
    [](const Vec<Val>& a, const Vec<Val>& b) {
      return a + b;
    }
  );
}

auto main() -> int {
  // double* a[] = {(double[]){1, 2, 3}, (double[]){4, 5, 6}};
  auto a = Mat<double>{{{1, 2, 3}, {4, 5, 6}}};
  std::cout << sizeof(a) << std::endl;
  std::cout << sum_across_cols(a) << std::endl;
  std::cout << sum_across_rows(a) << std::endl;
}
