#include <cstdlib>
#include <memory>
#include <vector>

// Dense only, not sparse.
template<typename Val>
struct Tensor {
  Tensor(const std::vector<size_t>& shape): sizes{shape} {
    // TODO Allocate vals.
  }

  auto rank() {return sizes.size();};

  auto operator[](std::initializer_list<size_t> coord) {
    return vals[index(coord)];
  }

private:
  size_t offset;
  std::vector<size_t> sizes;
  std::vector<size_t> strides;
  std::shared_ptr<std::vector<Val>> vals;

  auto index(std::initializer_list<size_t> coord) -> size_t {
    return 0;
  }
};

auto main() -> int {
  //
}
