#include <algorithm>
#include <array>
#include <cstdlib>
#include <numeric>

using Scalar = double;

template<size_t Size>
// using Vector = Scalar[Size];
// struct Vector{Scalar items[Size];};
using Vector = std::array<Scalar, Size>;

template<size_t Size>
auto operator+(const Vector<Size>& a, const Vector<Size>& b) -> Vector<Size> {
  auto sum = Vector<Size>{};
  for (auto i = size_t{}; i < a.size(); i += 1) {
    sum[i] = a[i] + b[i];
  }
  // std::transform(a.begin(), a.end(), b.begin(), sum,
  //   [](Scalar x, Scalar y) {
  //     return x + y;
  //   }
  // );
  return sum;
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
}
