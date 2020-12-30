#include <vector>

template<typename Item>
using Tensor = std::vector<Item>;

template<typename Item>
auto sum(const Tensor<Item>& tensor) -> Tensor<Item> {
  //
}
