#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

// using Scal = double;

template<typename Scal>
using Vec = std::vector<Scal>;

template<typename Scal>
using Mat = std::vector<Vec<Scal>>;

template<typename Scal>
auto operator+(const Vec<Scal>& a, const Vec<Scal>& b) -> Vec<Scal> {
  auto sum = Vec<Scal>(a.size());
  std::transform(a.cbegin(), a.cend(), b.cbegin(), sum.begin(),
    [](Scal x, Scal y) {
      return x + y;
    }
  );
  return sum;
}

template<typename Scal>
auto operator<<(std::ostream& out, const Vec<Scal>& a) -> std::ostream& {
  for (const auto& x: a | std::ranges::views::take(1)) {
    out << x;
  }
  for (const auto& x: a | std::ranges::views::drop(1)) {
    out << " " << x;
  }
  return out;
}

template<typename Scal>
auto sum_across_cols(const Mat<Scal>& matrix) -> Vec<Scal> {
  auto sum = Vec<Scal>(matrix.size());
  std::transform(matrix.cbegin(), matrix.cend(), sum.begin(),
    [](const Vec<Scal>& row) {
      return std::reduce(row.cbegin(), row.cend());
    }
  );
  return sum;
}

template<typename Scal>
auto sum_across_rows(const Mat<Scal>& matrix) -> Vec<Scal> {
  // No control of shape if empty!
  auto m = matrix.empty() ? 0 : matrix[0].size();
  return std::reduce(matrix.cbegin(), matrix.cend(), Vec<Scal>(m),
    [](const Vec<Scal>& a, const Vec<Scal>& b) {
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
