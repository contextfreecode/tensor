#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using Scalar = double;

template<typename Scalar>
using Vector = std::vector<Scalar>;

template<typename Scalar>
using Matrix = std::vector<Vector<Scalar>>;

template<typename Scalar>
auto operator+(const Vector<Scalar>& a, const Vector<Scalar>& b)
  -> Vector<Scalar>
{
  auto sum = Vector<Scalar>(a.size());
  std::transform(a.cbegin(), a.cend(), b.cbegin(), sum.begin(),
    [](Scalar x, Scalar y) {
      return x + y;
    }
  );
  return sum;
}

template<typename Scalar>
auto operator<<(std::ostream& out, const Vector<Scalar>& a) -> std::ostream& {
  for (const auto& x: a | std::ranges::views::take(1)) {
    out << x;
  }
  for (const auto& x: a | std::ranges::views::drop(1)) {
    out << " " << x;
  }
  return out;
}

template<typename Scalar>
auto sum_across_cols(const Matrix<Scalar>& matrix) -> Vector<Scalar> {
  auto sum = Vector<Scalar>(matrix.size());
  std::transform(matrix.cbegin(), matrix.cend(), sum.begin(),
    [](const Vector<Scalar>& row) {
      return std::reduce(row.cbegin(), row.cend());
    }
  );
  return sum;
}

template<typename Scalar>
auto sum_across_rows(const Matrix<Scalar>& matrix) -> Vector<Scalar> {
  auto ncol = matrix.empty() ? 0 : matrix[0].size();
  return std::reduce(matrix.cbegin(), matrix.cend(), Vector<Scalar>(ncol),
    [](const Vector<Scalar>& a, const Vector<Scalar>& b) {
      return a + b;
    }
  );
}

auto main() -> int {
  // double* a[2] = {(double[]){1, 2, 3}, (double[]){4, 5, 6}};
  // Scalar a[2][3] = {{1, 2, 3}, {4, 5, 6}};
  auto a = Matrix<double>{{1, 2, 3}, {4, 5, 6}};
  std::cout << sizeof(a) << std::endl;
  std::cout << sum_across_cols(a) << std::endl;
  std::cout << sum_across_rows(a) << std::endl;
}
