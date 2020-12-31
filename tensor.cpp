#include <cstdlib>
#include <memory>
#include <vector>

template<typename Val>
struct Tensor {
  std::vector<size_t> shape;
  // Ownership?!?!? Views?!?!?
  std::shared_ptr<std::vector<Val>> vals;
};

auto main() -> int {
  //
}
