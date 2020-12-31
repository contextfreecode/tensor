#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>

// using Scal = double;

template<typename Scal, size_t N>
// using Vec = Scalar[N];
using Vec = std::array<Scal, N>;
// struct Vec {
//   Scalar items[N];
//   auto cbegin() const {return items;} auto cend() const {return items + N;}
//   auto begin() const {return cbegin();} auto end() const {return cend();}
//   auto begin() {return items;} auto end() {return items + N;}
// };

template<typename Scal, size_t N, size_t M>
// using Mat = Scalar[N][M];
using Mat = std::array<Vec<Scal, M>, N>;

template<typename Scal, size_t N>
auto operator+(const Vec<Scal, N>& a, const Vec<Scal, N>& b) -> Vec<Scal, N> {
  auto sum = Vec<Scal, N>{};
  std::transform(a.cbegin(), a.cend(), b.cbegin(), sum.begin(),
    [](Scal x, Scal y) {
      return x + y;
    }
  );
  return sum;
}

template<typename Scal, size_t N>
auto operator<<(std::ostream& out, const Vec<Scal, N>& a) -> std::ostream& {
  for (const auto& x: a | std::ranges::views::take(1)) {
    out << x;
  }
  for (const auto& x: a | std::ranges::views::drop(1)) {
    out << " " << x;
  }
  return out;
}

template<typename Scal, size_t N, size_t M>
auto sum_across_cols(const Mat<Scal, N, M>& matrix) -> Vec<Scal, N> {
  auto sum = Vec<Scal, N>{};
  std::transform(matrix.cbegin(), matrix.cend(), sum.begin(),
    [](const Vec<Scal, M>& row) {
      return std::reduce(row.cbegin(), row.cend());
    }
  );
  return sum;
}

template<typename Scal, size_t N, size_t M>
auto sum_across_rows(const Mat<Scal, N, M>& matrix) -> Vec<Scal, M> {
  return std::reduce(matrix.cbegin(), matrix.cend(), Vec<Scal, M>{},
    [](const Vec<Scal, M>& a, const Vec<Scal, M>& b) {
      return a + b;
    }
  );
}

auto main() -> int {
  // double a[2][3] = {{1, 2, 3}, {4, 5, 6}};
  auto a = Mat<double, 2, 3>{{{1, 2, 3}, {4, 5, 6}}};
  std::cout << sizeof(a) << std::endl;
  std::cout << sum_across_cols(a) << std::endl;
  std::cout << sum_across_rows(a) << std::endl;
}
