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
    sizes_ = {row.size()};
    init();
    *vals_ = row;
  }

  Tensor(std::initializer_list<std::initializer_list<Val>> rows) {
    sizes_ = {
      Index(rows.size()), rows.size() ? Index(rows.begin()->size()) : 0,
    };
    init();
    for (auto& row: rows) {
      auto begin = vals_->begin() + sizes_[1] * (&row - rows.begin());
      std::copy(row.begin(), row.end(), begin);
    }
  }

  static auto zeros(const std::vector<Index>& shape) -> Tensor<Val> {
    auto result = Tensor<Val>{};
    result.sizes_ = shape;
    result.init();
    return result;
  }

  auto offset() const -> Index {return offset_;}

  auto operator[](std::initializer_list<Index> coord) const -> Val {
    std::cout << "index: " << index(coord) << std::endl;
    return vals_->at(index(coord));
  }

  auto operator()(std::convertible_to<Index> auto... coord) const -> Val {
    return (*this)[{Index(coord)...}];
  }

  auto rank() const {return sizes_.size();}

  auto sizes() const -> const std::vector<Index> {return sizes_;}

  auto strides() const -> const std::vector<Index> {return strides_;}

  auto vals() const -> const std::vector<Val>& {return *vals_;}

private:
  Index offset_ = 0;
  std::vector<Index> sizes_;
  std::vector<Index> strides_;
  std::shared_ptr<std::vector<Val>> vals_;

  auto index(std::initializer_list<Index> coord) const -> Index {
    return std::transform_reduce(
      coord.begin(), coord.end(), strides_.cbegin(), offset_
    );
  }

  auto init() -> void {
    strides_.resize(sizes_.size());
    // Calculate strides in row majorish order back to front.
    // Imperative seems easier here at the moment and good enough.
    auto stride = 1;
    for (auto i = sizes_.size(); i; i -= 1) {
      strides_[i - 1] = stride;
      stride *= sizes_[i - 1];
    }
    // Final "stride" is for the whole array size.
    vals_ = std::make_shared<std::vector<Val>>(stride);
  }
};

template<typename Val>
auto mean(const Tensor<Val>& a, Index axis) -> Tensor<Val> {
  return {};
}

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
  std::cout << b(1, 2) << std::endl;
  auto m = mean(b, 0);
}
