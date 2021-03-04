#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <vector>

auto copy_except(
  const std::ranges::random_access_range auto& items,
  std::integral auto index
) {
  auto result = typename std::remove_reference<decltype(items)>::type();
  result.reserve(items.size() - 1);
  std::copy(items.begin(), items.begin() + index, std::back_inserter(result));
  std::copy(items.begin() + index + 1, items.end(), std::back_inserter(result));
  return result;
}

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

using Index = std::ptrdiff_t;

template<typename Val>
struct Tensor {
  Tensor() {
    // TODO Efficient scalar with value 0?
  }

  Tensor(std::initializer_list<Val> row) {
    sizes_ = {Index(row.size())};
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

  auto at_by_dim(Index index, Index dim = 0) -> Tensor<Val> {
    auto result = Tensor<Val>{};
    result.offset_ = offset_ + index * strides_.at(dim);
    result.sizes_ = copy_except(sizes_, dim);
    result.strides_ = copy_except(strides_, dim);
    result.vals_ = vals_;
    return result;
  }

  auto ndim() const -> Index {return sizes_.size();}

  auto offset() const -> Index {return offset_;}

  auto operator[](std::initializer_list<Index> coord) const -> Val {
    // std::cout << "index: " << index(coord) << std::endl;
    return vals_->at(index(coord));
  }

  auto operator()(std::convertible_to<Index> auto... coord) const -> Val {
    return (*this)[{Index(coord)...}];
  }

  auto sizes() const -> const std::vector<Index>& {return sizes_;}

  auto strides() const -> const std::vector<Index>& {return strides_;}

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

template<typename Item>
auto operator<<(std::ostream& out, const std::vector<Item>& items) -> auto& {
  write_items(out, items, ' ');
  return out;
}

template<typename Val>
auto describe(std::ostream& out, const Tensor<Val>& tensor) {
  std::cout << "offset " << tensor.offset() << std::endl;
  std::cout << "sizes " << tensor.sizes() << std::endl;
  std::cout << "strides " << tensor.strides() << std::endl;
}

// template<typename Val>
// auto mean(const Tensor<Val>& a, Index axis) -> Tensor<Val> {
//   return {};
// }

auto main() -> int {
  // auto a = Tensor<double>::zeros({2, 3});
  // auto a = Tensor<double>{{1, 2, 3}, {4, 5, 6}};
  auto a = Tensor{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
  describe(std::cout, a);
  std::cout
    << a[{0, 0}] << ' ' << a[{0, 1}] << ' ' << a[{0, 2}] << std::endl
    << a[{1, 0}] << ' ' << a[{1, 1}] << ' ' << a[{1, 2}] << std::endl;
  // std::cout
  //   << a(0, 0) << ' ' << a(0, 1) << ' ' << a(0, 2) << std::endl
  //   << a(1, 0) << ' ' << a(1, 1) << ' ' << a(1, 2) << std::endl;
  // Row.
  // std::cout << "row" << std::endl;
  // auto row = a.at_by_dim(1, 0);
  // describe(std::cout, row);
  // std::cout << row(0) << " " << row(1) << " " << row(2) << std::endl;
  // Cols.
  // std::cout << "cols" << std::endl;
  // for (auto j = 0; j < a.sizes().at(1); j += 1) {
  //   auto col = a.at_by_dim(j, 1);
  //   // describe(std::cout, col);
  //   std::cout << col(0) << " " << col(1) << std::endl;
  // }
}
