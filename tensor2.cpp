#include <cstdlib>
#include <type_traits>

template<typename Array>
struct Tensor {
  typename std::remove_extent<Array>::type* vals;
};

template<typename Array, size_t Axis>
auto sum_across_axis(Array a) -> std::remove_extent<Array, Axis>::type {
  //
}

auto main() -> int {
  double vals[][3] = {{1, 2, 3}, {4, 5, 6}};
  auto a = Tensor<double[2][3]>{vals};
}
