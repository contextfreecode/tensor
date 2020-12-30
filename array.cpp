#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>

using Scalar = double;

template<size_t Size>
// using Vector = Scalar[Size];
// struct Vector{Scalar items[Size];};
using Vector = std::array<Scalar, Size>;

template<size_t Size>
auto operator+(const Vector<Size>& a, const Vector<Size>& b) -> Vector<Size> {
  auto sum = Vector<Size>{};
  std::transform(a.begin(), a.end(), b.begin(), sum.begin(),
    [](Scalar x, Scalar y) {
      return x + y;
    }
  );
  return sum;
}

template<size_t Size>
auto operator<<(std::ostream& out, const Vector<Size>& a) -> std::ostream& {
  for (const auto& x: a | std::ranges::views::take(1)) {
    out << x;
  }
  for (const auto& x: a | std::ranges::views::drop(1)) {
    out << " " << x;
  }
  return out;
}

template<size_t NRow, size_t NCol>
// using Matrix = Scalar[NRow][NCol];
using Matrix = std::array<Vector<NCol>, NRow>;

template<size_t NRow, size_t NCol>
auto sum_across_rows(const Matrix<NRow, NCol>& matrix) -> Vector<NCol> {
  return std::reduce(matrix.begin(), matrix.end(), Vector<NCol>{},
    [](const Vector<NCol>& a, const Vector<NCol>& b) {
      return a + b;
    }
  );
}

auto main() -> int {
  // Scalar a[2][3] = {{1, 2, 3}, {4, 5, 6}};
  auto a = Matrix<2, 3>{{{1, 2, 3}, {4, 5, 6}}};
  auto b = sum_across_rows(a);
  std::cout << b << std::endl;
}
