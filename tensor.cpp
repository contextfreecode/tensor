#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

// Dense only, not sparse.
template<typename Val>
struct Tensor {
  Tensor(const std::vector<size_t>& shape):
    sizes{shape},
    strides(sizes.size())
  {
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

  auto rank() {return sizes.size();};

  auto operator[](std::initializer_list<size_t> coord) {
    std::cout << "index: " << index(coord) << std::endl;
    return vals->at(index(coord));
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
};

auto main() -> int {
  auto a = Tensor<double>({2, 3});
  std::cout << a[{0, 0}] << std::endl;
  std::cout << a[{1, 2}] << std::endl;
}
