#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

// Dense only, not sparse.
template<typename Val>
struct Tensor {
  Tensor() {
    //
  }

  Tensor(std::initializer_list<Val> v) {
    sizes = {v.size()};
    init();
    *vals = v;
  }

  Tensor(std::initializer_list<std::initializer_list<Val>> v) {
    sizes = {v.size(), v.size() ? v.begin()->size() : 0};
    init();
    // TODO Go simple for loop begin to end here???
    std::for_each(
      v.begin(), v.end(), [&](const std::initializer_list<Val>& row) {
        // TODO Verify lengths.
        auto begin = vals->begin() + sizes[1] * (&row - v.begin());
        std::copy(row.begin(), row.end(), begin);
      }
    );
  }

  static auto zeros(const std::vector<size_t>& shape) -> Tensor<Val> {
    auto result = Tensor<Val>{};
    result.sizes = shape;
    result.init();
    return result;
  }

  auto rank() {return sizes.size();};

  auto operator[](std::initializer_list<size_t> coord) -> Val {
    std::cout << "index: " << index(coord) << std::endl;
    return vals->at(index(coord));
  }

  auto operator()(std::unsigned_integral auto... coord) -> Val {
    return (*this)[{coord...}];
  }

private:
  size_t offset = 0;
  std::vector<size_t> sizes;
  std::vector<size_t> strides;
  std::shared_ptr<std::vector<Val>> vals;

  auto index(std::initializer_list<size_t> coord) -> size_t {
    return std::transform_reduce(
      coord.begin(), coord.end(), strides.cbegin(), offset
    );
  }

  auto init() -> void {
    strides.resize(sizes.size());
    // Calculate strides in row majorish order back to front.
    // Imperative seems easier here at the moment and good enough.
    size_t stride = 1;
    for (size_t i = sizes.size(); i; i -= 1) {
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
  std::cout << b(1u, 2u) << std::endl;
}
