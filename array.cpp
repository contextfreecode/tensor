#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>
#include <type_traits>

template<typename Val>
using Scalar = Val;

template<typename Val, size_t N>
using Vec = std::array<Val, N>;
// using Vec = Val[N];
// struct Vec {
//   Val items[N];
//   auto  begin()       {return items;}   auto  end()       {return items + N;}
//   auto  begin() const {return items;}   auto  end() const {return items + N;}
//   auto cbegin() const {return begin();} auto cend() const {return end();}
// };

template<typename Val, size_t N, size_t M>
using Mat = Vec<Vec<Val, M>, N>;
// using Mat = Val[N][M];

auto write_items(
  std::ostream& out, const std::ranges::range auto& a, auto sep
) -> void {
  for (const auto& x: a | std::ranges::views::take(1)) {
    out << x;
  }
  for (const auto& x: a | std::ranges::views::drop(1)) {
    out << sep << x;
  }
}

template<typename Val, size_t N>
auto operator<<(std::ostream& out, const Vec<Val, N>& a) -> std::ostream& {
  write_items(out, a, ' ');
  return out;
}

template<typename Val, size_t N>
auto operator+(const Vec<Val, N>& a, const Vec<Val, N>& b) -> Vec<Val, N> {
  auto sum = Vec<Val, N>{};
  std::transform(a.cbegin(), a.cend(), b.cbegin(), sum.begin(),
    [](Val x, Val y) {
      return x + y;
    }
  );
  return sum;
}

template<typename Val, size_t N, size_t M>
auto sum_col(const Mat<Val, N, M>& matrix) -> Vec<Val, N> {
  auto sum = Vec<Val, N>{};
  std::transform(matrix.cbegin(), matrix.cend(), sum.begin(),
    [](const Vec<Val, M>& row) {
      return std::reduce(row.cbegin(), row.cend());
    }
  );
  return sum;
}

template<typename Val, size_t N, size_t M>
auto sum_row(const Mat<Val, N, M>& matrix) -> Vec<Val, M> {
  return std::reduce(matrix.cbegin(), matrix.cend(), Vec<Val, M>{},
    [](const auto& a, const auto& b) {
      return a + b;
    }
  );
}

auto main() -> int {
  // Remember valgrind and overhead. (1 alloc even without the next line.)
  // std::cout << "Hi!" << std::endl;
  // See also: nm -an array | c++filt | grep sum_
  // auto x = Scalar<double>{1};

  using Val = double;
  Val a[][3] = {{1, 2, 3}, {4, 5, 6}};
  printf("%td\n", sizeof a);
  printf("%td\n", sizeof a[0]);

  // Val* b[] = {(Val[]){1, 2, 3}, (Val[]){4, 5, 6}};
  // printf("%td\n", sizeof b);
  // printf("%td\n", sizeof b[0]);

  // Val b0[] = {1, 2, 3}, b1[] = {4, 5, 6};
  // Val* b[] = {b0, b1};

  // std::cout << "ndim " << std::rank<decltype(a)>::value << std::endl;
  // std::cout << "nrow " << std::extent<decltype(a)>::value << std::endl;
  // std::cout << "ncol " << std::extent<decltype(a), 1>::value << std::endl;

  // auto mat = Mat<double, 2, 3>{{{1, 2, 3}, {4, 5, 6}}};
  // std::cout << sizeof(mat) << std::endl;
  // std::cout << sum_row(mat) << std::endl;
  // std::cout << sum_col(mat) << std::endl;
}
