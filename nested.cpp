#include <vector>

template<typename Item>
using Tensor = std::vector<Item>;

template<typename Item>
auto sum(const Tensor<Item>& tensor) -> Tensor<Item> {
  //
}

int main(void) {
  double* a[2] = {(double[]){1, 2, 3}, (double[]){4, 5, 6}};
}
