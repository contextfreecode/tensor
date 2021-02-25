#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

using Index = std::ptrdiff_t;

// Dense only, not sparse.
template<typename Val>
struct Tensor {
  Tensor() {
    //
  }

  Tensor(std::initializer_list<Val> row) {
    sizes = {row.size()};
    init();
    *vals = row;
  }

  Tensor(std::initializer_list<std::initializer_list<Val>> rows) {
    sizes = {Index(rows.size()), rows.size() ? Index(rows.begin()->size()) : 0};
    init();
    for (auto& row: rows) {
      auto begin = vals->begin() + sizes[1] * (&row - rows.begin());
      std::copy(row.begin(), row.end(), begin);
    }
  }

  static auto zeros(const std::vector<Index>& shape) -> Tensor<Val> {
    auto result = Tensor<Val>{};
    result.sizes = shape;
    result.init();
    return result;
  }

  auto rank() {return sizes.size();};

  auto operator[](std::initializer_list<Index> coord) -> Val {
    std::cout << "index: " << index(coord) << std::endl;
    return vals->at(index(coord));
  }

  auto operator()(std::convertible_to<Index> auto... coord) -> Val {
    return (*this)[{Index(coord)...}];
  }

private:
  Index offset = 0;
  std::vector<Index> sizes;
  std::vector<Index> strides;
  std::shared_ptr<std::vector<Val>> vals;

  auto index(std::initializer_list<Index> coord) -> Index {
    return std::transform_reduce(
      coord.begin(), coord.end(), strides.cbegin(), offset
    );
  }

  auto init() -> void {
    strides.resize(sizes.size());
    // Calculate strides in row majorish order back to front.
    // Imperative seems easier here at the moment and good enough.
    auto stride = 1;
    for (auto i = sizes.size(); i; i -= 1) {
      strides[i - 1] = stride;
      stride *= sizes[i - 1];
    }
    // Final "stride" is for the whole array size.
    vals = std::make_shared<std::vector<Val>>(stride);
  }
};

auto main() -> int {
  auto a = Tensor<double>::zeros({2, 3});
  std::cout << a[{0, 0}] << std::endl;
  std::cout << a[{1, 0}] << std::endl;
  std::cout << a[{1, 2}] << std::endl;
  // auto b = Tensor<double>{{1, 2, 3}, {4, 5, 6}};
  auto b = Tensor{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
  std::cout << b[{0, 0}] << std::endl;
  std::cout << b[{1, 0}] << std::endl;
  std::cout << b[{1, 2}] << std::endl;
  std::cout << b(1, 2.0) << std::endl;
}
