#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>

using Scalar = double;

template<size_t Size>
// using Vector = Scalar[Size];
using Vector = std::array<Scalar, Size>;
// struct Vector {
//   Scalar items[Size];
//   auto cbegin() const {return items;} auto cend() const {return items + Size;}
//   auto begin() const {return cbegin();} auto end() const {return cend();}
//   auto begin() {return items;} auto end() {return items + Size;}
// };

template<size_t NRow, size_t NCol>
// using Matrix = Scalar[NRow][NCol];
using Matrix = std::array<Vector<NCol>, NRow>;

template<size_t Size>
auto operator+(const Vector<Size>& a, const Vector<Size>& b) -> Vector<Size> {
  auto sum = Vector<Size>{};
  std::transform(a.cbegin(), a.cend(), b.cbegin(), sum.begin(),
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
auto sum_across_cols(const Matrix<NRow, NCol>& matrix) -> Vector<NRow> {
  auto sum = Vector<NRow>{};
  std::transform(matrix.cbegin(), matrix.cend(), sum.begin(),
    [](const Vector<NCol>& row) {
      return std::reduce(row.cbegin(), row.cend());
    }
  );
  return sum;
}

template<size_t NRow, size_t NCol>
auto sum_across_rows(const Matrix<NRow, NCol>& matrix) -> Vector<NCol> {
  return std::reduce(matrix.cbegin(), matrix.cend(), Vector<NCol>{},
    [](const Vector<NCol>& a, const Vector<NCol>& b) {
      return a + b;
    }
  );
}

auto main() -> int {
  // Scalar a[2][3] = {{1, 2, 3}, {4, 5, 6}};
  auto a = Matrix<2, 3>{{{1, 2, 3}, {4, 5, 6}}};
  std::cout << sizeof(a) << std::endl;
  std::cout << sum_across_cols(a) << std::endl;
  std::cout << sum_across_rows(a) << std::endl;
}
